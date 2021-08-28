#include <stdio.h>
#include <stdint.h>

#include <string>
#include <vector>
#include <exception>

static std::exception e;

class quests_file;

template <typename T> class vector : public std::vector<T>
{
public:
	void read(quests_file *);
	void write(quests_file *);
};

class string : public std::string
{
public:
	void read(quests_file *);
	void write(quests_file *);
};

class uid
{
public:
	uint8_t id[16];

	void read(quests_file *);
	void write(quests_file *);
};

class token_list
{
public:
	vector<string> tokens;
	
	void read(quests_file *);
	void write(quests_file *);
};

class task
{
public:
	uid id2;
	uint32_t id1;
	uint32_t state;
	uint8_t inProgress;
	vector<uint32_t> objectives;

	void read(quests_file *);
	void write(quests_file *);
};

class quest
{
public:
	uint32_t id1;
	uid id2;
	vector<task> tasks;

	void read(quests_file *);
	void write(quests_file *);
};

class quest_list
{
public:
	vector<quest> quests;

	void read(quests_file *);
	void write(quests_file *);
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

class quests_file
{
private:
	FILE *fp;
	uint32_t key;
	uint32_t table[256];

public:
	uid id;
	token_list tokens;
	quest_list quests;

	void read(const char *);
	void write(const char *);

private:
	void read_key()
	{
		uint32_t k;

		if (fread(&k, 4, 1, fp) != 1)
			throw e;

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
			throw e;

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
			throw e;

		uint32_t ret = val ^ key;

		update_key(&val, 4);

		return ret;
	}

	uint8_t read_byte()
	{
		uint8_t val;

		if (fread(&val, 1, 1, fp) != 1)
			throw e;

		uint8_t ret = val ^ key;

		update_key(&val, 1);

		return ret;
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
		{
			throw e;
		}

		if (next_int())
			throw e;
	}

	void write_int(uint32_t val)
	{
		if (fwrite(&val, 4, 1, fp) != 1)
			throw e;
	}

	void write_byte(uint8_t val)
	{
		if (fwrite(&val, 1, 1, fp) != 1)
			throw e;
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
			throw e;

		write_int(pos - b->end);

		if (fseek(fp, pos, SEEK_SET))
			throw e;

		write_int(0);
	}
};

void quests_file::read(const char *filename)
{
	file f(filename, "rb");

	if (!(fp = f.fp))
		throw e;

	if (fseek(fp, 0, SEEK_END))
		throw e;
		
	long end = ftell(fp);

	if (fseek(fp, 0, SEEK_SET))
		throw e;

	read_key();

	if (read_int() != 0x58545351)
		throw e;

	if (read_int() != 0)
		throw e;

	id.read(this);
	tokens.read(this);
	quests.read(this);

	if (ftell(fp) != end)
		throw e;
}

void quests_file::write(const char *filename)
{
	file f(filename, "wb");

	if (!(fp = f.fp))
		throw e;

	write_int(0x55555555);
	write_int(0x58545351);
	write_int(0);

	id.write(this);
	tokens.write(this);
	quests.write(this);

	if (fflush(fp))
		throw e;
}

template <typename T> void vector<T>::read(quests_file *gdd)
{
	uint32_t n = gdd->read_int();

	this->resize(n);
	T *ptr = this->data();

	for (uint32_t i = 0; i < n; i++)
	{
		ptr[i].read(gdd);
	}
}

template <typename T> void vector<T>::write(quests_file *gdd)
{
	uint32_t n = this->size();
	gdd->write_int(n);

	T *ptr = this->data();
	for (uint32_t i = 0; i < n; i++)
	{
		ptr[i].write(gdd);
	}
}

void token_list::read(quests_file *gdd)
{
	block b;

	if (gdd->read_block_start(&b) != 10)
		throw e;

	if (gdd->read_int() != 2) // version
		throw e;

	tokens.read(gdd);

	gdd->read_block_end(&b);
}

void token_list::write(quests_file *gdd)
{
	block b;

	gdd->write_block_start(&b, 10);
	gdd->write_int(2); // version

	tokens.write(gdd);

	gdd->write_block_end(&b);
}

void quest_list::read(quests_file *gdd)
{
	block b;

	if (gdd->read_block_start(&b) != 11)
		throw e;

	if (gdd->read_int() != 3) // version
		throw e;

	quests.read(gdd);

	gdd->read_block_end(&b);
}

void quest_list::write(quests_file *gdd)
{
	block b;

	gdd->write_block_start(&b, 11);
	gdd->write_int(3); // version

	quests.write(gdd);

	gdd->write_block_end(&b);
}

void quest::read(quests_file *gdd)
{
	block b;

	id1 = gdd->read_int();
	id2.read(gdd);

	if (gdd->read_block_start(&b))
		throw e;

	tasks.read(gdd);

	gdd->read_block_end(&b);
}

void quest::write(quests_file *gdd)
{
	block b;

	gdd->write_int(id1);
	id2.write(gdd);

	gdd->write_block_start(&b, 0);

	tasks.write(gdd);

	gdd->write_block_end(&b);
}

void task::read(quests_file *gdd)
{
	block b;

	id1 = gdd->read_int();
	id2.read(gdd);

	if (gdd->read_block_start(&b))
		throw e;

	state = gdd->read_int();
	inProgress = gdd->read_byte();

	uint32_t n = (b.len - 5) / 4;

	objectives.resize(n);

	for (uint32_t i = 0; i < n; i++)
	{
		objectives[i] = gdd->read_int();
	}

	gdd->read_block_end(&b);
}

void task::write(quests_file *gdd)
{
	block b;

	gdd->write_int(id1);
	id2.write(gdd);

	gdd->write_block_start(&b, 0);

	gdd->write_int(state);
	gdd->write_byte(inProgress);

	uint32_t n = objectives.size();
	
	for (uint32_t i = 0; i < n; i++)
	{
		gdd->write_int(objectives[i]);
	}

	gdd->write_block_end(&b);
}

void uid::read(quests_file *gdd)
{
	for (unsigned i = 0; i < 16; i++)
	{
		id[i] = gdd->read_byte();
	}
}

void uid::write(quests_file *gdd)
{
	for (unsigned i = 0; i < 16; i++)
	{
		gdd->write_byte(id[i]);
	}
}

void string::read(quests_file *gdd)
{
	uint32_t len = gdd->read_int();

	clear();
	reserve(len);

	for (uint32_t i = 0; i < len; i++)
	{
		push_back(gdd->read_byte());
	}
}

void string::write(quests_file *gdd)
{
	uint32_t len = size();
	const char *str = data();

	gdd->write_int(len);

	for (uint32_t i = 0; i < len; i++)
	{
		gdd->write_byte(str[i]);
	}
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <in file> <out file>\n", argv[0]);
		return 1;
	}

	quests_file quests;

	try
	{
		quests.read(argv[1]);
	}
	catch (const std::exception &e)
	{
		printf("Error reading file: %s\n", argv[1]);
		return 1;
	}

	try
	{
		quests.write(argv[2]);
	}
	catch (const std::exception &e)
	{
		printf("Error writing file: %s\n", argv[2]);
		return 1;
	}

	return 0;
}
