/*
This is a decryption tool for the Grim Dawn transfer.gst (softcore) or transfer.gsh (hardcore) file, compatible with Grim Dawn version 1.1.9.1 with both Ashes of Malmouth and Forgotten Gods expansions and Crucible DLC.
The original version of this file was written by "Christopher" and can be found at https://www.lost.org.uk/grimdawn.html. Nearly all credit goes to them.
*/

#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <inttypes.h>

#include <string>
#include <vector>
#include <exception>

typedef std::string string;

static std::exception e;

class stash_file;

template <typename T> class vector : public std::vector<T>
{
public:
	void read(stash_file *);
	void write(stash_file *);
};

class item
{
public:
	string baseName;
	string prefixName;
	string suffixName;
	string modifierName;
	string transmuteName;
	string componentName;
	string relicBonus;
	string augmentName;
	uint32_t stackCount;
	uint32_t seed;
	uint32_t componentSeed;
	uint32_t unknown;
	uint32_t augmentSeed;
	uint32_t var1;
	float xOffset;
	float yOffset;

	void read(stash_file *);
	void write(stash_file *);
	void print();
};

class sack
{
public:
	vector<item> items;
	uint32_t width;
	uint32_t height;

	void read(stash_file *);
	void write(stash_file *);
	void print();
};

class file
{
public:
	FILE *fp;

	file(const char *name, const char *mode)
	{
		fp = fopen(name, mode);
	}

	~file()
	{
		if (fp) fclose(fp);
	}

private:
	file(const file &); // = delete;
	file &operator=(const file &); // = delete;
};

struct block
{
	uint32_t len;
	long end;
};

class stash_file
{
private:
	FILE *fp;
	uint32_t key;
	uint32_t table[256];

public:
	vector<sack> sacks;
	string mod;

	void read(const char *);
	void write(const char *);

private:
	void read_key()
	{
		uint32_t k;

		if (fread(&k, 4, 1, fp) != 1)
			throw std::runtime_error("Error in read_key.");

		k ^= 0x55555555;

		key = k;

		for (unsigned i = 0; i < 256; i++)
		{
			k = (k >> 1) | (k << 31);
			k *= 39916801;
			table[i] = k;
		}
	}

	uint32_t next_int()
	{
		uint32_t ret;

		if (fread(&ret, 4, 1, fp) != 1)
			throw std::runtime_error("Error in next_int.");

		ret ^= key;

		return ret;
	}

	void update_key(void *ptr, unsigned len)
	{
		uint8_t *p = (uint8_t *)ptr;

		for (unsigned i = 0; i < len; i++)
		{
			key ^= table[p[i]];
		}
	}

public:
	uint32_t read_int()
	{
		uint32_t val;

		if (fread(&val, 4, 1, fp) != 1)
			throw std::runtime_error("Error in read_int.");

		uint32_t ret = val ^ key;

		update_key(&val, 4);

		return ret;
	}

	uint8_t read_byte()
	{
		uint8_t val;

		if (fread(&val, 1, 1, fp) != 1){
			if (ferror(fp)){
				perror("fread error");
				throw std::runtime_error("Error in read_byte.");
			}
			else{
				if (feof(fp)){
					throw std::runtime_error("Error in read_byte: end of file reached.");
				}
				throw std::runtime_error("Error in read_byte.");
			}
		}

		uint8_t ret = val ^ key;

		update_key(&val, 1);

		return ret;
	}

	float read_float()
	{
		union { float f; int i; } u;
		u.i = read_int();
		return u.f;
	}

	void read_str(string *str)
	{
		uint32_t len = read_int();

		str->clear();
		str->reserve(len);

		for (uint32_t i = 0; i < len; i++)
		{
			str->push_back(read_byte());
		}
	}

	uint32_t read_block_start(block *b)
	{
		uint32_t ret = read_int();

		b->len = next_int();
		b->end = ftell(fp) + b->len;

		return ret;
	}

	void read_block_end(block *b)
	{
		if (ftell(fp) != b->end)
			throw std::runtime_error("read_block_end: expected ftell to read end of block.");

		if (next_int())
			throw std::runtime_error("read_block_end: expected end-of-block character 0.");
	}

	void write_int(uint32_t val)
	{
		if (fwrite(&val, 4, 1, fp) != 1)
			throw std::runtime_error("Error in write_int.");
	}

	void write_byte(uint8_t val)
	{
		if (fwrite(&val, 1, 1, fp) != 1)
			throw std::runtime_error("Error in write_byte.");
	}

	void write_float(float val)
	{
		if (fwrite(&val, 4, 1, fp) != 1)
			throw std::runtime_error("Error in write_float.");
	}

	void write_str(string *str)
	{
		uint32_t len = str->size();

		write_int(len);

		if (len && fwrite(str->data(), len, 1, fp) != 1)
			throw std::runtime_error("Error in write_string.");
	}

	void write_block_start(block *b, uint32_t n)
	{
		write_int(n);
		write_int(0);
		b->end = ftell(fp);
	}

	void write_block_end(block *b)
	{
		long pos = ftell(fp);

		if (fseek(fp, b->end - 4, SEEK_SET))
			throw std::runtime_error("write_block_end error.");

		write_int(pos - b->end);

		if (fseek(fp, pos, SEEK_SET))
			throw std::runtime_error("write_block_end error.");

		write_int(0);
	}
};

template <typename T> void vector<T>::read(stash_file *stash)
{
	uint32_t n = stash->read_int();

	this->resize(n);
	T *ptr = this->data();

	for (uint32_t i = 0; i < n; i++)
	{
		ptr[i].read(stash);
	}
}

template <typename T> void vector<T>::write(stash_file *stash)
{
	uint32_t n = this->size();
	stash->write_int(n);

	T *ptr = this->data();
	for (uint32_t i = 0; i < n; i++)
	{
		ptr[i].write(stash);
	}
}

void stash_file::read(const char *filename)
{
	file f(filename, "rb");

	if (!(fp = f.fp))					throw e;
	if (fseek(fp, 0, SEEK_END)) 		throw e;
	long end = ftell(fp);
	if (fseek(fp, 0, SEEK_SET)) 		throw e;

	read_key();

	if (read_int() != 2) 				throw std::runtime_error("Expected to read specific int 2.");

	block b;

	if (read_block_start(&b) != 18)		throw std::runtime_error("Expected read_block_start to return 18.");
	if (read_int() != 5) 				throw std::runtime_error("Expected to read version 5."); // Version
	if (next_int())						throw std::runtime_error("Expected to read specific int 0.");
	read_str(&mod);
	if (read_byte() != 3){				throw std::runtime_error("Expected to read specific byte 3."); }
	
	sacks.read(this);

	read_block_end(&b);
	if (ftell(fp) != end) 				throw std::runtime_error("Expected ftell to report end of file.");
}

void stash_file::write(const char *filename)
{
	file f(filename, "wb");

	if (!(fp = f.fp)) 					throw e;

	write_int(0x55555555);
	write_int(2);

	block b;

	write_block_start(&b, 18);

	write_int(5); // version;
	write_int(0);
	write_str(&mod);
	write_byte(3);
	sacks.write(this);

	write_block_end(&b);

	if (fflush(fp))						throw e;
}

void sack::read(stash_file *stash)
{
	block b;

	stash->read_block_start(&b);

	width = stash->read_int();
	height = stash->read_int();
	
	items.read(stash);

	stash->read_block_end(&b);
}

void sack::write(stash_file *stash)
{
	block b;

	stash->write_block_start(&b, 0);

	stash->write_int(width);
	stash->write_int(height);
	items.write(stash);

	stash->write_block_end(&b);
}

void sack::print()
{
	printf("sack:\n");
	printf("  width  = %" PRIu32 "\n", width);
	printf("  height = %" PRIu32 "\n", height);
	printf("  item ct= %i\n", items.size());
	printf("  items:\n");
	for(int i = 0; i < items.size(); i++){
		items[i].print();
	}
}

void item::read(stash_file *stash)
{	
	stash->read_str(&baseName);
	stash->read_str(&prefixName);
	stash->read_str(&suffixName);
	stash->read_str(&modifierName);
	stash->read_str(&transmuteName);
	seed = stash->read_int();
	stash->read_str(&componentName);
	stash->read_str(&relicBonus);
	componentSeed = stash->read_int();
	stash->read_str(&augmentName);
	unknown = stash->read_int();
	augmentSeed = stash->read_int();
	var1 = stash->read_int();
	stackCount = stash->read_int();
	xOffset = stash->read_float();
	yOffset = stash->read_float();
}

void item::write(stash_file *stash)
{
	stash->write_str(&baseName);
	stash->write_str(&prefixName);
	stash->write_str(&suffixName);
	stash->write_str(&modifierName);
	stash->write_str(&transmuteName);
	stash->write_int(seed);
	stash->write_str(&componentName);
	stash->write_str(&relicBonus);
	stash->write_int(componentSeed);
	stash->write_str(&augmentName);
	stash->write_int(unknown);
	stash->write_int(augmentSeed);
	stash->write_int(var1);
	stash->write_int(stackCount);
	stash->write_float(xOffset);
	stash->write_float(yOffset);
}

void item::print()
{
	printf("    item:\n");
	printf("      baseName      = %s\n", this->baseName.c_str());
	printf("      prefixName    = %s\n", this->prefixName.c_str());
	printf("      suffixName    = %s\n", this->suffixName.c_str());
	printf("      modifierName  = %s\n", this->modifierName.c_str());
	printf("      transmuteName = %s\n", this->transmuteName.c_str());
	printf("      seed          = %" PRIu32 "\n", this->seed);
	printf("      componentName = %s\n", this->componentName.c_str());
	printf("      relicBonus    = %s\n", this->relicBonus.c_str());
	printf("      componentSeed = %" PRIu32 "\n", this->componentSeed);
	printf("      augmentName   = %s\n", this->augmentName.c_str());
	printf("      unknown       = %" PRIu32 "\n", this->unknown);
	printf("      augmentSeed   = %" PRIu32 "\n", this->augmentSeed);
	printf("      var1          = %" PRIu32 "\n", this->var1);
	printf("      stackCount    = %" PRIu32 "\n", this->stackCount);
	printf("      xOffset       = %f\n", this->xOffset);
	printf("      yOffset       = %f\n", this->yOffset);
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <in file> <out file>\n", argv[0]);
		return 1;
	}

	stash_file stash;

	try
	{
		stash.read(argv[1]);
	}
	catch (const std::exception &e)
	{
		printf("Error reading file: %s", e.what());
		return 1;
	}

	try
	{
		stash.write(argv[2]);
	}
	catch (const std::exception &e)
	{
		printf("Error writing file: %s", e.what());
		return 1;
	}

	return 0;
}
