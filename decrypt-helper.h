#ifndef decrypthelper
#define decrypthelper

class stash_file;
class gdc_file;



template <typename T> class vector : public std::vector<T>
{
public:
	void read(gdc_file *);
	void read(stash_file *);
    void write(gdc_file *);
	void write(stash_file *);
};

class string : public std::string
{
public:
	void read(gdc_file *);
	void write(gdc_file *);
};

class wstring : public std::wstring
{
public:
	void read(gdc_file *);
	void write(gdc_file *);
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

	void read(gdc_file *);
	void read(stash_file *);
    void write(gdc_file *);
	void write(stash_file *);
	void print();
};

class stash_item : public item
{
public:
	float x;
	float y;

	void read(gdc_file *);
    void read(stash_file *);
	void write(gdc_file *);
    void write(stash_file *);
	void print();
};

class stash_tab
{
public:
	vector<stash_item> items;
	uint32_t width;
	uint32_t height;

	void read(gdc_file *);
	void read(stash_file *);
    void write(gdc_file *);
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

#endif