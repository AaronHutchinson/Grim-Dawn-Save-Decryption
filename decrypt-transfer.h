#ifndef decrypttransfer
#define decrypttransfer

//typedef std::string string;

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
	vector<stash_tab> tabs;
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