#ifndef decrypttransfer
#define decrypttransfer

typedef std::string string;
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

	file(const char *name, const char *mode);
	~file();

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
    void read_key();
    uint32_t next_int();
    void update_key(void *ptr, unsigned len);

public:
	vector<sack> sacks;
	string mod;

	void read(const char *);
	void write(const char *);
    uint32_t read_int();
    uint8_t read_byte();
    float read_float();
    void read_str(string *str);
    uint32_t read_block_start(block *b);
    void read_block_end(block *b);
    void write_int(uint32_t val);
    void write_byte(uint8_t val);
    void write_float(float val);
    void write_str(string *str);
    void write_block_start(block *b, uint32_t n);
    void write_block_end(block *b);
};

#endif