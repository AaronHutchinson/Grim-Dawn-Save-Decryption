#ifndef decryptplayer
#define decryptplayer

class uid
{
public:
	uint8_t id[16];

	void read(gdc_file *);
	void write(gdc_file *);
	void print();
};

class header
{
public:
	wstring name;
	string tag;
	uint32_t level;
	uint8_t sex;
	uint8_t hardcore;

	void read(gdc_file *);
	void write(gdc_file *);
	void print();
};

class character_info
{
public:
	string texture;
	uint32_t money;
	uint32_t lootMode [39];
	uint32_t currentTribute;
	uint32_t unknown;
	uint8_t isInMainQuest;
	uint8_t hasBeenInGame;
	uint8_t difficulty;
	uint8_t greatestDifficulty;
	uint8_t greatestSurvivalDifficulty;
	uint8_t compassState;
	uint8_t skillWindowShowHelp;
	uint8_t weaponSwapActive;
	uint8_t weaponSwapEnabled;

	void read(gdc_file *);
	void write(gdc_file *);
	void print();
};

class character_bio
{
public:
	uint32_t level;
	uint32_t experience;
	uint32_t attributePointsUnspent;
	uint32_t skillPointsUnspent;
	uint32_t devotionPointsUnspent;
	uint32_t totalDevotionUnlocked;
	float physique;
	float cunning;
	float spirit;
	float health;
	float energy;

	void read(gdc_file *);
	void write(gdc_file *);
	void print();
};

class inventory_item : public item
{
public:
	uint32_t x;
	uint32_t y;

	void read(gdc_file *);
	void write(gdc_file *);
};

class inventory_sack
{
public:
	vector<inventory_item> items;
	uint8_t tempBool;

	void read(gdc_file *);
	void write(gdc_file *);
	void print();
};

class inventory_equipment : public item
{
public:
	uint8_t attached;

	void read(gdc_file *);
	void write(gdc_file *);
};

class inventory
{
public:
	uint32_t numBags;
	vector<inventory_sack> sacks;
	inventory_equipment equipment[12];
	inventory_equipment weapon1[2];
	inventory_equipment weapon2[2];
	uint32_t focused;
	uint32_t selected;
	uint8_t flag;
	uint8_t useAlternate;
	uint8_t alternate1;
	uint8_t alternate2;

	void read(gdc_file *);
	void write(gdc_file *);
	void print();
};

class character_stash
{
public:
	vector<stash_tab> tabs;
	uint32_t stashTabsPurchased;

	void read(gdc_file *);
	void write(gdc_file *);
	void print();
};

class respawn_list
{
public:
	vector<uid> uids[3];
	uid spawn[3];

	void read(gdc_file *);
	void write(gdc_file *);
};

class teleport_list
{
public:
	vector<uid> uids[3];

	void read(gdc_file *);
	void write(gdc_file *);
};

class marker_list
{
public:
	vector<uid> uids[3];

	void read(gdc_file *);
	void write(gdc_file *);
};

class shrine_list
{
public:
	vector<uid> uids[6];

	void read(gdc_file *);
	void write(gdc_file *);
};

class skill
{
public:
	string name;
	string autoCastSkill;
	string autoCastController;
	uint32_t level;
	uint32_t devotionLevel;
	uint32_t experience;
	uint32_t active;
	uint8_t enabled;
	uint8_t unknown1;
	uint8_t unknown2;

	void read(gdc_file *);
	void write(gdc_file *);
};

class item_skill
{
public:
	string name;
	string autoCastSkill;
	string autoCastController;
	string itemName;
	uint32_t itemSlot;

	void read(gdc_file *);
	void write(gdc_file *);
};

class character_skills
{
public:
	vector<skill> skills;
	vector<item_skill> itemSkills;
	uint32_t masteriesAllowed;
	uint32_t skillReclamationPointsUsed;
	uint32_t devotionReclamationPointsUsed;

	void read(gdc_file *);
	void write(gdc_file *);
};

class lore_notes
{
public:
	vector<string> names;

	void read(gdc_file *);
	void write(gdc_file *);
};

class faction_data
{
public:
	float value;
	float positiveBoost;
	float negativeBoost;
	uint8_t modified;
	uint8_t unlocked;

	void read(gdc_file *);
	void write(gdc_file *);
};

class faction_pack
{
public:
	vector<faction_data> factions;
	uint32_t faction;

	void read(gdc_file *);
	void write(gdc_file *);
};

class hot_slot
{
public:
	string skill;
	string item;
	string bitmapUp;
	string bitmapDown;
	wstring label;
	uint32_t type;
	uint32_t equipLocation;
	uint8_t isItemSkill;
	
	void read(gdc_file *);
	void write(gdc_file *);
	void print();
};

class ui_settings
{
public:
	hot_slot slots[46];
	string unknown4[5];
	string unknown5[5];
	uint32_t unknown2;
	float cameraDistance;
	uint8_t unknown6[5];
	uint8_t unknown1;
	uint8_t unknown3;

	void read(gdc_file *);
	void write(gdc_file *);
	void print();
};

class tutorial_pages
{
public:
	vector<uint32_t> pages;
	
	void read(gdc_file *);
	void write(gdc_file *);
};

class unknown_data
{
public:
	string str;
	uint32_t num;
};

class play_stats
{
public:
	string greatestMonsterKilledName[3];
	string lastMonsterHit[3];
	string lastMonsterHitBy[3];
	uint32_t greatestMonsterKilledLevel[3];
	uint32_t greatestMonsterKilledLifeAndMana[3];
	uint32_t bossKills[3];
	uint32_t playTime;
	uint32_t deaths;
	uint32_t kills;
	uint32_t experienceFromKills;
	uint32_t healthPotionsUsed;
	uint32_t manaPotionsUsed;
	uint32_t maxLevel;
	uint32_t hitsReceived;
	uint32_t hitsInflicted;
	uint32_t criticalHitsInflicted;
	uint32_t criticalHitsReceived;
	uint32_t championKills;
	uint32_t heroKills;	
	uint32_t itemsCrafted;
	uint32_t relicsCrafted;
	uint32_t transcendentRelicsCrafted;
	uint32_t mythicalRelicsCrafted;
	uint32_t shrinesRestored;
	uint32_t oneShotChestsOpened;
	uint32_t loreNotesCollected;
	float greatestDamageInflicted;
	float lastHit;
	float lastHitBy;
	float greatestDamageReceived;
	uint32_t survivalWaveTier;		// Crucible
	uint32_t greatestSurvivalScore;	// Crucible
	uint32_t cooldownRemaining;		// Number of Crucible defenses built?
	uint32_t cooldownTotal;			// Number of Crucible blessings used?

	uint32_t v_length;				// Length of vector v
	vector<unknown_data> v;			// Usage unknown

	uint32_t shatteredRealmSouls;
	uint32_t shatteredRealmEssence;
	uint8_t difficultySkip;

	uint32_t unknown1;
	uint32_t unknown2;

	void read(gdc_file *);
	void write(gdc_file *);
	void print();
};

class trigger_tokens
{
public:
	vector<string> tokens[3];

	void read(gdc_file *);
	void write(gdc_file *);
	void print();
};

class gdc_file
{
private:
	FILE *fp;
	uint32_t key;
	uint32_t table[256];

    void read_key();
    uint32_t next_int();
    void update_key(void *ptr, uint32_t len);

public:
	header hdr;
	uid id;
	character_info info;
	character_bio bio;
	inventory inv;
	character_stash stash;
	respawn_list respawns;
	teleport_list teleports;
	marker_list markers;
	shrine_list shrines;
	character_skills skills;
	lore_notes notes;
	faction_pack factions;
	ui_settings ui;
	tutorial_pages tutorials;
	play_stats stats;
	trigger_tokens tokens;

	void read(const char *);
	void write(const char *);
    uint32_t read_int();
    uint16_t read_short();
    uint8_t read_byte();
    float read_float();
    uint32_t read_block_start(block *b);
    void read_block_end(block *b);
    void write_int(uint32_t val);
    void write_short(uint16_t val);
    void write_byte(uint8_t val);
    void write_float(float val);
    void write_block_start(block *b, uint32_t n);
    void write_block_end(block *b);

};

#endif