/*
This is a decryption tool for Grim Dawn player.gdc files, compatible with Grim Dawn version 1.1.9.1 with both Ashes of Malmouth and Forgotten Gods expansions and Crucible DLC.
The original version of this file was written by "Christopher" and can be found at https://www.lost.org.uk/grimdawn.html. Nearly all credit goes to them.
*/

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <iostream>

#include <string>
#include <vector>
#include <exception>

static std::exception e;

class gdc_file;

template <typename T> class vector : public std::vector<T>
{
public:
	void read(gdc_file *);
	void write(gdc_file *);
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

class uid
{
public:
	uint8_t id[16];

	void read(gdc_file *);
	void write(gdc_file *);
	void print();
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

class stash_item : public item
{
public:
	float x;
	float y;

	void read(gdc_file *);
	void write(gdc_file *);
	void print();
};

class character_stash_tab
{
public:
	vector<stash_item> items;
	uint32_t width;
	uint32_t height;

	void read(gdc_file *);
	void write(gdc_file *);
	void print();
};

class character_stash
{
public:
	vector<character_stash_tab> tabs;
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

class gdc_file
{
private:
	FILE *fp;
	uint32_t key;
	uint32_t table[256];

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

	void update_key(void *ptr, uint32_t len)
	{
		uint8_t *p = (uint8_t *)ptr;

		for (uint32_t i = 0; i < len; i++)
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

	uint16_t read_short()
	{
		uint16_t val;

		if (fread(&val, 2, 1, fp) != 1)
			throw std::runtime_error("Error in read_short.");

		uint16_t ret = val ^ key;

		update_key(&val, 2);

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
			throw std::runtime_error("read_block_end: expected ftell to read end of block.");
		}

		if (next_int())
			throw std::runtime_error("read_block_end: expected end-of-block character 0.");
	}

	void write_int(uint32_t val)
	{
		if (fwrite(&val, 4, 1, fp) != 1)
			throw std::runtime_error("Error in write_int.");
	}

	void write_short(uint16_t val)
	{
		if (fwrite(&val, 2, 1, fp) != 1)
			throw std::runtime_error("Error in write_short.");
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

	int reader_position(){
		return ftell(fp);
	}
};



void gdc_file::read(const char *filename)
{
	file f(filename, "rb");
	if (!(fp = f.fp)){ 				throw e; }
	if (fseek(fp, 0, SEEK_END)){	throw e; }
	long end = ftell(fp);
	if (fseek(fp, 0, SEEK_SET)){ 	throw e; }

	read_key();
	if (read_int()  != 0x58434447){ throw std::runtime_error("Expected to read specific hex 0x58434447."); }
	if (read_int()  != 2){ 			throw std::runtime_error("Expected to read specific int 2."); }
	hdr.read(this);
	if (read_byte() != 3){			throw std::runtime_error("Expected to read specific byte 3."); }
	if (next_int()  != 0){  		throw std::runtime_error("Expected to read specific int 0."); }
	uint32_t ver = read_int(); 	// version
    if (ver != 8){ 					throw std::runtime_error("Expected to read gdc_file version 8."); }

	id.read(this);
	info.read(this);
	bio.read(this);
	inv.read(this);
	stash.read(this);
	respawns.read(this);
	teleports.read(this);
	markers.read(this);
	shrines.read(this);
	skills.read(this);
	notes.read(this);
	factions.read(this);
	ui.read(this);
	tutorials.read(this);
	stats.read(this);
	tokens.read(this);

	if (ftell(fp) != end){			throw std::runtime_error("Expected end of file."); }
}

void gdc_file::write(const char *filename)
{
	file f(filename, "wb");

	if (!(fp = f.fp)) {throw e;}

	write_int(0x55555555);
	write_int(0x58434447);
	write_int(2);

	hdr.write(this);

	write_byte(3);
	write_int(0);
	write_int(8); // version

	id.write(this);
	info.write(this);
	bio.write(this);
	inv.write(this);
	stash.write(this);
	respawns.write(this);
	teleports.write(this);
	markers.write(this);
	shrines.write(this);
	skills.write(this);
	notes.write(this);
	factions.write(this);
	ui.write(this);
	tutorials.write(this);
	stats.write(this);
	tokens.write(this);

	if (fflush(fp))	{throw e;}
}

template <typename T> void vector<T>::read(gdc_file *gdc)
{
	uint32_t n = gdc->read_int();

	this->resize(n);
	T *ptr = this->data();

	for (uint32_t i = 0; i < n; i++)
	{
		ptr[i].read(gdc);
	}
}

template <typename T> void vector<T>::write(gdc_file *gdc)
{
	uint32_t n = this->size();
	gdc->write_int(n);

	T *ptr = this->data();
	for (uint32_t i = 0; i < n; i++)
	{
		ptr[i].write(gdc);
	}
}

void header::read(gdc_file *gdc)
{
	name.read(gdc);
	sex = gdc->read_byte();
	tag.read(gdc);
	level = gdc->read_int();
	hardcore = gdc->read_byte();
}

void header::write(gdc_file *gdc)
{
	name.write(gdc);
	gdc->write_byte(sex);
	tag.write(gdc);
	gdc->write_int(level);
	gdc->write_byte(hardcore);
}

void header::print()
{
	printf("Character header:\n");
	printf("  Name     = %ls\n", this->name.c_str());
	printf("  Sex      = %hhu\n", this->sex);
	printf("  Tag      = %s\n", this->tag.c_str());
	printf("  Level    = %u\n", this->level);
	printf("  Hardcore = %hhu\n", this->hardcore);
}

void character_info::read(gdc_file *gdc)
{
	block b;

	if (gdc->read_block_start(&b) != 1)
		throw std::runtime_error("read_block_start of character_info not equal to 1.");

	if (gdc->read_int() != 5) // version
		throw std::runtime_error("incorrect version of character_info.");

	isInMainQuest = gdc->read_byte();
	hasBeenInGame = gdc->read_byte();
	difficulty = gdc->read_byte();
	greatestDifficulty = gdc->read_byte();
	money = gdc->read_int();
	greatestSurvivalDifficulty = gdc->read_byte();
	currentTribute = gdc->read_int();
	compassState = gdc->read_byte();
	skillWindowShowHelp = gdc->read_byte();
	weaponSwapActive = gdc->read_byte();
	weaponSwapEnabled = gdc->read_byte();
	texture.read(gdc);
	unknown = gdc->read_int();

	// Loot filter settings. Each read byte should be either 0 or 1
	// Quality
	lootMode[ 0] = gdc->read_byte(); // Common
	lootMode[ 1] = gdc->read_byte(); // Magical
	lootMode[ 2] = gdc->read_byte(); // Rare
	lootMode[ 3] = gdc->read_byte(); // Monster Infrequent
	lootMode[ 4] = gdc->read_byte(); // Epic
	lootMode[ 5] = gdc->read_byte(); // Legendary
	lootMode[ 6] = gdc->read_byte(); // Sets
	lootMode[ 7] = gdc->read_byte(); // Always Show Uniques
	// Type
	lootMode[ 8] = gdc->read_byte(); // 1h Melee
	lootMode[ 9] = gdc->read_byte(); // 2h Melee
	lootMode[10] = gdc->read_byte(); // 1h Ranged
	lootMode[11] = gdc->read_byte(); // 2h Ranged
	lootMode[12] = gdc->read_byte(); // Dagger/Scepter
	lootMode[13] = gdc->read_byte(); // Caster Off-Hand
	lootMode[14] = gdc->read_byte(); // Shield
	lootMode[15] = gdc->read_byte(); // Armor
	lootMode[16] = gdc->read_byte(); // Accessories
	lootMode[17] = gdc->read_byte(); // Components
	// Damage
	lootMode[18] = gdc->read_byte(); // Physical
	lootMode[19] = gdc->read_byte(); // Pierce
	lootMode[20] = gdc->read_byte(); // Fire
	lootMode[21] = gdc->read_byte(); // Cold
	lootMode[22] = gdc->read_byte(); // Lightning
	lootMode[23] = gdc->read_byte(); // Acid
	lootMode[24] = gdc->read_byte(); // Vitality
	lootMode[25] = gdc->read_byte(); // Aether
	lootMode[26] = gdc->read_byte(); // Chaos
	lootMode[27] = gdc->read_byte(); // Bleed
	lootMode[28] = gdc->read_byte(); // Pet Bonuses
	// Player
	lootMode[29] = gdc->read_byte(); // My Masteries
	lootMode[30] = gdc->read_byte(); // Other Masteries
	lootMode[31] = gdc->read_byte(); // Speed
	lootMode[32] = gdc->read_byte(); // Cooldown Reduction
	lootMode[33] = gdc->read_byte(); // Crit Damage
	lootMode[34] = gdc->read_byte(); // Offensive Ability
	lootMode[35] = gdc->read_byte(); // Defensive Ability
	lootMode[36] = gdc->read_byte(); // Resistances
	lootMode[37] = gdc->read_byte(); // Retaliation

	lootMode[38] = gdc->read_byte(); // Always Show Double Rare

	gdc->read_block_end(&b);
}

void character_info::write(gdc_file *gdc)
{
	block b;

	gdc->write_block_start(&b, 1);
	gdc->write_int(5); //version

	gdc->write_byte(isInMainQuest);
	gdc->write_byte(hasBeenInGame);
	gdc->write_byte(difficulty);
	gdc->write_byte(greatestDifficulty);
	gdc->write_int(money);
	gdc->write_byte(greatestSurvivalDifficulty);
	gdc->write_int(currentTribute);
	gdc->write_byte(compassState);
	gdc->write_byte(skillWindowShowHelp);
	gdc->write_byte(weaponSwapActive);
	gdc->write_byte(weaponSwapEnabled);
	texture.write(gdc);
	gdc->write_int(unknown);
	for(int i = 0; i < 39; i++)
		gdc->write_byte(lootMode[i]);

	gdc->write_block_end(&b);
}

void character_info::print(){
	printf("character_info:\n");
	printf("  isInMainQuest = %hhu\n", this->isInMainQuest);
	printf("  hasBeenInGame = %hhu\n", this->hasBeenInGame);
	printf("  difficulty = %hhu\n", this->difficulty);
	printf("  greatestDifficulty = %hhu\n", this->greatestDifficulty);
	printf("  money = %" PRIu32 "\n", this->money);
	printf("  greatestSurvivalDifficulty = %hhu\n", this->greatestSurvivalDifficulty);
	printf("  currentTribute = %" PRIu32 "\n", this->currentTribute);
	printf("  compassState = %hhu\n", this->compassState);
	std::string str = std::to_string(this->lootMode[0]);
	for (int i = 1; i < 39; i++){
		str = str + "," + std::to_string(this->lootMode[i]);
	}
	printf("  lootMode = %s\n", str.c_str());
	printf("  skillWindowShowHelp = %hhu\n", this->skillWindowShowHelp);
	printf("  weaponSwapActive = %hhu\n", this->weaponSwapActive);
	printf("  weaponSwapEnabled = %hhu\n", this->weaponSwapEnabled);
	printf("  texture = %s\n", this->texture.c_str());

}

void character_bio::read(gdc_file *gdc)
{
	block b;

	if (gdc->read_block_start(&b) != 2)
		throw std::runtime_error("Expected character_bio read_block_start to return 2.");

	if (gdc->read_int() != 8) // version
		throw std::runtime_error("Expected character_bio version to be 8.");

	level = gdc->read_int();
	experience = gdc->read_int();
	attributePointsUnspent = gdc->read_int();
	skillPointsUnspent = gdc->read_int();
	devotionPointsUnspent = gdc->read_int();
	totalDevotionUnlocked = gdc->read_int();
	physique = gdc->read_float();
	cunning = gdc->read_float();
	spirit = gdc->read_float();
	health = gdc->read_float();
	energy = gdc->read_float();

	gdc->read_block_end(&b);
}

void character_bio::write(gdc_file *gdc)
{
	block b;

	gdc->write_block_start(&b, 2);
	gdc->write_int(8); // version

	gdc->write_int(level);
	gdc->write_int(experience);
	gdc->write_int(attributePointsUnspent);
	gdc->write_int(skillPointsUnspent);
	gdc->write_int(devotionPointsUnspent);
	gdc->write_int(totalDevotionUnlocked);
	gdc->write_float(physique);
	gdc->write_float(cunning);
	gdc->write_float(spirit);
	gdc->write_float(health);
	gdc->write_float(energy);

	gdc->write_block_end(&b);
}

void character_bio::print(){
	printf("character_bio:\n");
	printf("  level                  = %" PRIu32 "\n", this->level);
	printf("  experience             = %" PRIu32 "\n", this->experience);
	printf("  attributePointsUnspent = %" PRIu32 "\n", this->attributePointsUnspent);
	printf("  skillPointsUnspent     = %" PRIu32 "\n", this->skillPointsUnspent);
	printf("  devotionPointsUnspent  = %" PRIu32 "\n", this->devotionPointsUnspent);
	printf("  totalDevotionUnlocked  = %" PRIu32 "\n", this->totalDevotionUnlocked);
	printf("  physique               = %f\n", this->physique);
	printf("  cunning                = %f\n", this->cunning);
	printf("  spirit                 = %f\n", this->spirit);
	printf("  health                 = %f\n", this->health);
	printf("  energy                 = %f\n", this->energy);

}

void inventory::read(gdc_file *gdc)
{
	block b;

	if (gdc->read_block_start(&b) != 3)
		throw std::runtime_error("Expected inventory read_block_start to return 3.");

	if (gdc->read_int() != 4) // version
		throw std::runtime_error("Expected inventory version to be 4.");

	if ((flag = gdc->read_byte()))
	{
		numBags = gdc->read_int();
		focused = gdc->read_int();
		selected = gdc->read_int();

		sacks.resize(numBags);

		for (uint32_t i = 0; i < numBags; i++)
		{
			sacks[i].read(gdc);
		}

		useAlternate = gdc->read_byte();

		for (unsigned i = 0; i < 12; i++)
		{
			equipment[i].read(gdc);
		}

		alternate1 = gdc->read_byte();

		for (unsigned i = 0; i < 2; i++)
		{
			weapon1[i].read(gdc);
		}

		alternate2 = gdc->read_byte();

		for (unsigned i = 0; i < 2; i++)
		{
			weapon2[i].read(gdc);
		}
	}

	gdc->read_block_end(&b);
}

void inventory::write(gdc_file *gdc)
{
	block b;

	gdc->write_block_start(&b, 3);
	gdc->write_int(4); // version

	gdc->write_byte(flag);

	if (flag)
	{
		gdc->write_int(numBags);
		gdc->write_int(focused);
		gdc->write_int(selected);

		for (uint32_t i = 0; i < numBags; i++)
		{
			sacks[i].write(gdc);
		}

		gdc->write_byte(useAlternate);

		for (unsigned i = 0; i < 12; i++)
		{
			equipment[i].write(gdc);
		}

		gdc->write_byte(alternate1);

		for (unsigned i = 0; i < 2; i++)
		{
			weapon1[i].write(gdc);
		}

		gdc->write_byte(alternate2);

		for (unsigned i = 0; i < 2; i++)
		{
			weapon2[i].write(gdc);
		}
	}

	gdc->write_block_end(&b);
}

void inventory::print(){
	printf("inventory:\n");
	if (this->flag){
		printf("  numBags  = %" PRIu32 "\n", this->numBags);
		printf("  focused  = %" PRIu32 "\n", this->focused);
		printf("  selected  = %" PRIu32 "\n", this->selected);
		for(int i = 0; i < this->numBags; i++){
			this->sacks[i].print();
		}
		printf("  useAlternate  = %hhu\n", this->useAlternate);
		printf("  equipment:\n");
		for(int i = 0; i < 12; i++){
			this->equipment[i].print();
		}
		printf("  alternate1  = %hhu\n", this->alternate1);
		printf("  weapon1:\n");
		for(int i = 0; i < 2; i++){
			this->weapon1[i].print();
		}
		printf("  alternate2  = %hhu\n", this->alternate2);
		printf("  weapon2:\n");
		for(int i = 0; i < 2; i++){
			this->weapon2[i].print();
		}
	}
	else{
		printf("  inventory null\n");
	}
	
}

void inventory_sack::read(gdc_file *gdc)
{
	block b;

	if (gdc->read_block_start(&b))
		throw std::runtime_error("Expected inventory_sack read_block_start to be nonzero.");

	tempBool = gdc->read_byte();
	items.read(gdc);

	gdc->read_block_end(&b);
}

void inventory_sack::write(gdc_file *gdc)
{
	block b;

	gdc->write_block_start(&b, 0);

	gdc->write_byte(tempBool);
	items.write(gdc);

	gdc->write_block_end(&b);
}

void inventory_sack::print(){
	for(int i = 0; i < this->items.size(); i++){
		this->items[i].print();
	}
}

void inventory_item::read(gdc_file *gdc)
{
	item::read(gdc);
	x = gdc->read_int();
	y = gdc->read_int();
}

void inventory_item::write(gdc_file *gdc)
{
	item::write(gdc);
	gdc->write_int(x);
	gdc->write_int(y);
}

void inventory_equipment::read(gdc_file *gdc)
{
	item::read(gdc);
	attached = gdc->read_byte();
}

void inventory_equipment::write(gdc_file *gdc)
{
	item::write(gdc);
	gdc->write_byte(attached);
}

void character_stash::read(gdc_file *gdc)
{
	block b;

	if (gdc->read_block_start(&b) != 4)
		throw std::runtime_error("Expected character_stash read_block_start to return 4.");

	if (gdc->read_int() != 6) // version
		throw std::runtime_error("Expected character_stash version to be 6.");
	
	stashTabsPurchased = gdc->read_int();
	tabs.resize(stashTabsPurchased);

	for(int i = 0; i < stashTabsPurchased; i++){
		tabs[i].read(gdc);
	}
	
	gdc->read_block_end(&b);
}

void character_stash::write(gdc_file *gdc)
{
	block b;

	gdc->write_block_start(&b, 4);
	gdc->write_int(6); // version

	gdc->write_int(stashTabsPurchased);
	for(int i = 0; i < stashTabsPurchased; i++){
		tabs[i].write(gdc);
	}

	gdc->write_block_end(&b);
}

void character_stash::print()
{
	printf("character_stash:\n");
	printf("  stashTabsPurchased = %" PRIu32 "\n", this->stashTabsPurchased);
	for (int i = 0; i < this->stashTabsPurchased; i++){
		this->tabs[i].print();
	}
}

void character_stash_tab::read(gdc_file *gdc)
{
	block b;

	if (gdc->read_block_start(&b) != 0){
		throw std::runtime_error("Expected character_stash_tab read_block_start to return 0.");
	}
	width = gdc->read_int();
	height = gdc->read_int();

	items.read(gdc);
	gdc->read_block_end(&b);
}

void character_stash_tab::write(gdc_file *gdc)
{
	block b;

	gdc->write_block_start(&b, 0);
	gdc->write_int(width);
	gdc->write_int(height);

	items.write(gdc);
	gdc->write_block_end(&b);
}

void character_stash_tab::print()
{
	printf("  character_stash_tab:\n");
	printf("    width     = %" PRIu32 "\n", width);
	printf("    height    = %" PRIu32 "\n", height);
	for(int i = 0; i < this->items.size(); i++){
		this->items[i].print();
	}
	
}

void stash_item::read(gdc_file *gdc)
{
	item::read(gdc);
	x = gdc->read_float();
	y = gdc->read_float();
}

void stash_item::write(gdc_file *gdc)
{
	item::write(gdc);
	gdc->write_float(x);
	gdc->write_float(y);
}

void stash_item::print()
{
	this->item::print();
	printf("      x = %f\n", this->x);
	printf("      y = %f\n", this->y);
}

void respawn_list::read(gdc_file *gdc)
{
	block b;

	if (gdc->read_block_start(&b) != 5)
		throw std::runtime_error("Expected respawn_list read_block_start to return 5.");

	if (gdc->read_int() != 1) // version
		throw std::runtime_error("Expected respawn_list version to be 1.");

	for (unsigned i = 0; i < 3; i++)
	{
		uids[i].read(gdc);
	}

	for (unsigned i = 0; i < 3; i++)
	{
		spawn[i].read(gdc);
	}

	gdc->read_block_end(&b);
}

void respawn_list::write(gdc_file *gdc)
{
	block b;

	gdc->write_block_start(&b, 5);
	gdc->write_int(1); // version

	for (unsigned i = 0; i < 3; i++)
	{
		uids[i].write(gdc);
	}

	for (unsigned i = 0; i < 3; i++)
	{
		spawn[i].write(gdc);
	}

	gdc->write_block_end(&b);
}

void teleport_list::read(gdc_file *gdc)
{
	block b;

	if (gdc->read_block_start(&b) != 6)
		throw std::runtime_error("Expected teleport_list read_block_start to return 6.");

	if (gdc->read_int() != 1) // version
		throw std::runtime_error("Expected teleport_list version to be 1.");

	for (unsigned i = 0; i < 3; i++)
	{
		uids[i].read(gdc);
	}
	
	gdc->read_block_end(&b);
}

void teleport_list::write(gdc_file *gdc)
{
	block b;

	gdc->write_block_start(&b, 6);
	gdc->write_int(1); // version

	for (unsigned i = 0; i < 3; i++)
	{
		uids[i].write(gdc);
	}

	gdc->write_block_end(&b);
}	

void marker_list::read(gdc_file *gdc)
{
	block b;

	if (gdc->read_block_start(&b) != 7)
		throw std::runtime_error("Expected marker_list read_block_start to return 7.");

	if (gdc->read_int() != 1) // version
		throw std::runtime_error("Expected marker_list version to be 1.");

	for (unsigned i = 0; i < 3; i++)
	{
		uids[i].read(gdc);
	}

	gdc->read_block_end(&b);
}

void marker_list::write(gdc_file *gdc)
{
	block b;

	gdc->write_block_start(&b, 7);
	gdc->write_int(1); // version

	for (unsigned i = 0; i < 3; i++)
	{
		uids[i].write(gdc);
	}

	gdc->write_block_end(&b);
}	

void shrine_list::read(gdc_file *gdc)
{
	block b;

	if (gdc->read_block_start(&b) != 17)
		throw std::runtime_error("Expected shrine_list read_block_start to return 17.");

	if (gdc->read_int() != 2) // version
		throw std::runtime_error("Expected shrine_list version to be 2.");

	for (unsigned i = 0; i < 6; i++)
	{
		uids[i].read(gdc);
	}

	gdc->read_block_end(&b);
}

void shrine_list::write(gdc_file *gdc)
{
	block b;

	gdc->write_block_start(&b, 17);
	gdc->write_int(2); // version

	for (unsigned i = 0; i < 6; i++)
	{
		uids[i].write(gdc);
	}

	gdc->write_block_end(&b);
}	

void character_skills::read(gdc_file *gdc)
{
	block b;

	if (gdc->read_block_start(&b) != 8)
		throw std::runtime_error("Expected character_skills read_block_start to return 8.");

	if (gdc->read_int() != 5) // version
		throw std::runtime_error("Expected character_skills version to be 5.");

	skills.read(gdc);
	masteriesAllowed = gdc->read_int();
	skillReclamationPointsUsed = gdc->read_int();
	devotionReclamationPointsUsed = gdc->read_int();
	itemSkills.read(gdc);

	gdc->read_block_end(&b);
}

void character_skills::write(gdc_file *gdc)
{
	block b;

	gdc->write_block_start(&b, 8);
	gdc->write_int(5); // version

	skills.write(gdc);
	gdc->write_int(masteriesAllowed);
	gdc->write_int(skillReclamationPointsUsed);
	gdc->write_int(devotionReclamationPointsUsed);
	itemSkills.write(gdc);

	gdc->write_block_end(&b);
}

void skill::read(gdc_file *gdc)
{
	name.read(gdc);
	level = gdc->read_int();
	enabled = gdc->read_byte();
	devotionLevel = gdc->read_int();
	experience = gdc->read_int();
	active = gdc->read_int();
	unknown1 = gdc->read_byte();
	unknown2 = gdc->read_byte();
	autoCastSkill.read(gdc);
	autoCastController.read(gdc);
}

void skill::write(gdc_file *gdc)
{
	name.write(gdc);
	gdc->write_int(level);
	gdc->write_byte(enabled);
	gdc->write_int(devotionLevel);
	gdc->write_int(experience);
	gdc->write_int(active);
	gdc->write_byte(unknown1);
	gdc->write_byte(unknown2);
	autoCastSkill.write(gdc);
	autoCastController.write(gdc);
}

void item_skill::read(gdc_file *gdc)
{
	name.read(gdc);
	autoCastSkill.read(gdc);
	autoCastController.read(gdc);
	itemSlot = gdc->read_int();
	itemName.read(gdc);
}

void item_skill::write(gdc_file *gdc)
{
	name.write(gdc);
	autoCastSkill.write(gdc);
	autoCastController.write(gdc);
	gdc->write_int(itemSlot);
	itemName.write(gdc);
}

void lore_notes::read(gdc_file *gdc)
{
	block b;

	if (gdc->read_block_start(&b) != 12)
		throw std::runtime_error("Expected lore_notes read_block_start to return 12.");

	if (gdc->read_int() != 1) // version
		throw std::runtime_error("Expected lore_notes version to be 1.");

	names.read(gdc);

	gdc->read_block_end(&b);
}

void lore_notes::write(gdc_file *gdc)
{
	block b;

	gdc->write_block_start(&b, 12);
	gdc->write_int(1); // version

	names.write(gdc);

	gdc->write_block_end(&b);
}

void faction_pack::read(gdc_file *gdc)
{
	block b;

	if (gdc->read_block_start(&b) != 13)
		throw std::runtime_error("Expected faction_pack read_block_start to return 13.");

	if (gdc->read_int() != 5) // version
		throw std::runtime_error("Expected faction_pack version to be 5.");

	faction = gdc->read_int();
	factions.read(gdc);

	gdc->read_block_end(&b);
}

void faction_pack::write(gdc_file *gdc)
{
	block b;

	gdc->write_block_start(&b, 13);
	gdc->write_int(5); // version

	gdc->write_int(faction);
	factions.write(gdc);

	gdc->write_block_end(&b);
}

void faction_data::read(gdc_file *gdc)
{
	modified = gdc->read_byte();
	unlocked = gdc->read_byte();
	value = gdc->read_float();
	positiveBoost = gdc->read_float();
	negativeBoost = gdc->read_float();
}

void faction_data::write(gdc_file *gdc)
{
	gdc->write_byte(modified);
	gdc->write_byte(unlocked);
	gdc->write_float(value);
	gdc->write_float(positiveBoost);
	gdc->write_float(negativeBoost);
}

void ui_settings::read(gdc_file *gdc)
{
	block b;

	if (gdc->read_block_start(&b) != 14)
		throw std::runtime_error("Expected ui_settings read_block_start to return 14.");

	if (gdc->read_int() != 5) // version
		throw std::runtime_error("Expected ui_settings version to be 5.");

	unknown1 = gdc->read_byte();
	unknown2 = gdc->read_int();
	unknown3 = gdc->read_byte();

	for (unsigned i = 0; i < 5; i++)
	{
		unknown4[i].read(gdc);
		unknown5[i].read(gdc);
		unknown6[i] = gdc->read_byte();
	}

	for (unsigned i = 0; i < 46; i++)
	{
		slots[i].read(gdc);
	}

	cameraDistance = gdc->read_float();

	gdc->read_block_end(&b);
}

void ui_settings::write(gdc_file *gdc)
{
	block b;

	gdc->write_block_start(&b, 14);
	gdc->write_int(5); // version

	gdc->write_byte(unknown1);
	gdc->write_int(unknown2);
	gdc->write_byte(unknown3);

	for (unsigned i = 0; i < 5; i++)
	{
		unknown4[i].write(gdc);
		unknown5[i].write(gdc);
		gdc->write_byte(unknown6[i]);
	}

	for (unsigned i = 0; i < 46; i++)
	{
		slots[i].write(gdc);
	}

	gdc->write_float(cameraDistance);

	gdc->write_block_end(&b);
}

void ui_settings::print()
{
	printf("ui_settings:\n");
	printf("  unknown1 = %hhu\n", unknown1);
	printf("  unknown2 = %" PRIu32 "\n", unknown2);
	printf("  unknown3 = %hhu\n", unknown3);

	for (unsigned i = 0; i < 5; i++)
	{
		printf("  unknown4[%i] = %s\n", i, unknown4[i].c_str());
		printf("  unknown5[%i] = %s\n", i, unknown5[i].c_str());
		printf("  unknown6[%i] = %hhu\n", i, unknown6[i]);
	}

	for (unsigned i = 0; i < 46; i++)
	{	
		printf("  slots[%i]:\n", i);
		slots[i].print();
	}

	printf("  cameraDistance = %f\n", cameraDistance);
	
}

void hot_slot::read(gdc_file *gdc)
{
	type = gdc->read_int();

	// 'type' mapping:
	//   0: regular skill
	//   2: health potion
	//   3: energy potion
	//   4294967295: empty

	// 'slot' mapping:
	//   0-9: primary action bar
	//    10: primary weapon set left click
	//    11: secondary weapon set left click
	//    12: primary weapon set right click
	//    13  secondary weapon set right click
	// 14-23: secondary action bar
	//    24: drink health potion
	//    25: drink energy potion
	//    26: stationary attack?
	// 27-35: ?

	if (type == 0)
	{
		skill.read(gdc);
		isItemSkill = gdc->read_byte();
		item.read(gdc);
		equipLocation = gdc->read_int();
	}
	else if (type == 4)
	{
		item.read(gdc);
		bitmapUp.read(gdc);
		bitmapDown.read(gdc);
		label.read(gdc);
	}
}

void hot_slot::write(gdc_file *gdc)
{
	gdc->write_int(type);

	if (type == 0)
	{
		skill.write(gdc);
		gdc->write_byte(isItemSkill);
		item.write(gdc);
		gdc->write_int(equipLocation);
	}
	else if (type == 4)
	{
		item.write(gdc);
		bitmapUp.write(gdc);
		bitmapDown.write(gdc);
		label.write(gdc);
	}
}

void hot_slot::print()
{
	printf("    type = %" PRIu32 "\n", type);

	if (type == 0)
	{
		printf("    skill         = %s\n", skill.c_str());
		printf("    isItemSkill   = %hhu\n", isItemSkill);
		printf("    item          = %s\n", item.c_str());
		printf("    equipLocation = %" PRIu32 "\n", equipLocation);
	}
	else if (type == 4)
	{
		printf("    item          = %s\n", item.c_str());
		printf("    bitmapUp      = %s\n", bitmapUp.c_str());
		printf("    bitmapDown    = %s\n", bitmapDown.c_str());
		printf("    label         = %ls\n", label.c_str());
	}
}

void tutorial_pages::read(gdc_file *gdc)
{
	block b;

	if (gdc->read_block_start(&b) != 15)
		throw std::runtime_error("Expected tutorial_pages read_block_start to return 15.");

	if (gdc->read_int() != 1) // version
		throw std::runtime_error("Expected tutorial_pages version to be 1.");

	uint32_t n = gdc->read_int();
	pages.resize(n);

	for (uint32_t i = 0; i < n; i++)
	{
		pages[i] = gdc->read_int();
	}

	gdc->read_block_end(&b);
}

void tutorial_pages::write(gdc_file *gdc)
{
	block b;

	gdc->write_block_start(&b, 15);
	gdc->write_int(1); // version

	uint32_t n = pages.size();
	gdc->write_int(n);

	for (uint32_t i = 0; i < n; i++)
	{
		gdc->write_int(pages[i]);
	}

	gdc->write_block_end(&b);
}

void play_stats::read(gdc_file *gdc)
{
	block b;

	if (gdc->read_block_start(&b) != 16)
		throw std::runtime_error("Expected play_stats read_block_start to return 16.");

	if (gdc->read_int() != 11) // version
		throw std::runtime_error("Expected play_stats version to be 11.");

	playTime = gdc->read_int();
	deaths = gdc->read_int();
	kills = gdc->read_int();
	experienceFromKills = gdc->read_int();
	healthPotionsUsed = gdc->read_int();
	manaPotionsUsed = gdc->read_int();
	maxLevel = gdc->read_int();
	hitsReceived = gdc->read_int();
	hitsInflicted = gdc->read_int();
	criticalHitsInflicted = gdc->read_int();
	criticalHitsReceived = gdc->read_int();
	greatestDamageInflicted = gdc->read_float();

	for (unsigned i = 0; i < 3; i++)
	{
		greatestMonsterKilledName[i].read(gdc);
		greatestMonsterKilledLevel[i] = gdc->read_int();
		greatestMonsterKilledLifeAndMana[i] = gdc->read_int();
		lastMonsterHit[i].read(gdc);
		lastMonsterHitBy[i].read(gdc);
	}

	championKills = gdc->read_int();
	lastHit = gdc->read_float();
	lastHitBy = gdc->read_float();
	greatestDamageReceived = gdc->read_float();
	heroKills = gdc->read_int();
	itemsCrafted = gdc->read_int();
	relicsCrafted = gdc->read_int();
	transcendentRelicsCrafted = gdc->read_int();
	mythicalRelicsCrafted = gdc->read_int();
	shrinesRestored = gdc->read_int();
	oneShotChestsOpened = gdc->read_int();
	loreNotesCollected = gdc->read_int();

	for (unsigned i = 0; i < 3; i++)
	{
		bossKills[i] = gdc->read_int();
	}

	survivalWaveTier = gdc->read_int();
	greatestSurvivalScore = gdc->read_int();
	cooldownRemaining = gdc->read_int();
	cooldownTotal = gdc->read_int();

	v_length = gdc->read_int();
	v.resize(v_length);
	for(int i = 0; i < v_length; i++){
		v[i].str.read(gdc);
		v[i].num = gdc->read_int();
	}

	shatteredRealmSouls = gdc->read_int();
	shatteredRealmEssence = gdc->read_int();
	difficultySkip = gdc->read_byte();

	unknown1 = gdc->read_int();
	unknown2 = gdc->read_int();

	gdc->read_block_end(&b);
}

void play_stats::write(gdc_file *gdc)
{
	block b;

	gdc->write_block_start(&b, 16);
	gdc->write_int(11); // version

	gdc->write_int(playTime);
	gdc->write_int(deaths);
	gdc->write_int(kills);
	gdc->write_int(experienceFromKills);
	gdc->write_int(healthPotionsUsed);
	gdc->write_int(manaPotionsUsed);
	gdc->write_int(maxLevel);
	gdc->write_int(hitsReceived);
	gdc->write_int(hitsInflicted);
	gdc->write_int(criticalHitsInflicted);
	gdc->write_int(criticalHitsReceived);
	gdc->write_float(greatestDamageInflicted);

	for (unsigned i = 0; i < 3; i++)
	{
		greatestMonsterKilledName[i].write(gdc);
		gdc->write_int(greatestMonsterKilledLevel[i]);
		gdc->write_int(greatestMonsterKilledLifeAndMana[i]);
		lastMonsterHit[i].write(gdc);
		lastMonsterHitBy[i].write(gdc);
	}

	gdc->write_int(championKills);
	gdc->write_float(lastHit);
	gdc->write_float(lastHitBy);
	gdc->write_float(greatestDamageReceived);
	gdc->write_int(heroKills);
	gdc->write_int(itemsCrafted);
	gdc->write_int(relicsCrafted);
	gdc->write_int(transcendentRelicsCrafted);
	gdc->write_int(mythicalRelicsCrafted);
	gdc->write_int(shrinesRestored);
	gdc->write_int(oneShotChestsOpened);
	gdc->write_int(loreNotesCollected);

	for (unsigned i = 0; i < 3; i++)
	{
		gdc->write_int(bossKills[i]);
	}

	gdc->write_int(survivalWaveTier);
	gdc->write_int(greatestSurvivalScore);
	gdc->write_int(cooldownRemaining);
	gdc->write_int(cooldownTotal);

	gdc->write_int(v_length);
	for(int i = 0; i < v_length; i++){
		v[i].str.write(gdc);
		gdc->write_int(v[i].num);
	}

	gdc->write_int(shatteredRealmSouls);
	gdc->write_int(shatteredRealmEssence);
	gdc->write_byte(difficultySkip);

	gdc->write_int(unknown1);
	gdc->write_int(unknown2);

	gdc->write_block_end(&b);
}

void play_stats::print()
{
	printf("play_stats:\n");
	printf("  greatestMonsterKilledName        = %s, %s, %s\n", this->greatestMonsterKilledName[0].c_str(), this->greatestMonsterKilledName[1].c_str(), this->greatestMonsterKilledName[2].c_str());
	printf("  lastMonsterHit                   = %s, %s, %s\n", this->lastMonsterHit[0].c_str(), this->lastMonsterHit[1].c_str(), this->lastMonsterHit[2].c_str());
	printf("  lastMonsterHitBy                 = %s, %s, %s\n", this->lastMonsterHitBy[0].c_str(), this->lastMonsterHitBy[1].c_str(), this->lastMonsterHitBy[2].c_str());
	printf("  greatestMonsterKilledLevel       = %" PRIu32 ", %" PRIu32 ", " PRIu32 "\n", this->greatestMonsterKilledLevel[0], this->greatestMonsterKilledLevel[1], this->greatestMonsterKilledLevel[2]);
	printf("  greatestMonsterKilledLifeAndMana = %" PRIu32 ", %" PRIu32 ", " PRIu32 "\n", this->greatestMonsterKilledLifeAndMana[0], this->greatestMonsterKilledLifeAndMana[1], this->greatestMonsterKilledLifeAndMana[2]);
	printf("  bossKills                        = %" PRIu32 ", %" PRIu32 ", " PRIu32 "\n", this->bossKills[0], this->bossKills[1], this->bossKills[2]);
	printf("  playTime                         = %" PRIu32 "\n", this->playTime);
	printf("  deaths                           = %" PRIu32 "\n", this->deaths);
	printf("  kills                            = %" PRIu32 "\n", this->kills);
	printf("  experienceFromKills              = %" PRIu32 "\n", this->experienceFromKills);
	printf("  healthPotionsUsed                = %" PRIu32 "\n", this->healthPotionsUsed);
	printf("  manaPotionsUsed                  = %" PRIu32 "\n", this->manaPotionsUsed);
	printf("  maxLevel                         = %" PRIu32 "\n", this->maxLevel);
	printf("  hitsReceived                     = %" PRIu32 "\n", this->hitsReceived);
	printf("  hitsInflicted                    = %" PRIu32 "\n", this->hitsInflicted);
	printf("  criticalHitsInflicted            = %" PRIu32 "\n", this->criticalHitsInflicted);
	printf("  criticalHitsReceived             = %" PRIu32 "\n", this->criticalHitsReceived);
	printf("  championKills                    = %" PRIu32 "\n", this->championKills);
	printf("  heroKills                        = %" PRIu32 "\n", this->heroKills);
	printf("  itemsCrafted                     = %" PRIu32 "\n", this->itemsCrafted);
	printf("  relicsCrafted                    = %" PRIu32 "\n", this->relicsCrafted);
	printf("  transcendentRelicsCrafted        = %" PRIu32 "\n", this->transcendentRelicsCrafted);
	printf("  mythicalRelicsCrafted            = %" PRIu32 "\n", this->mythicalRelicsCrafted);
	printf("  shrinesRestored                  = %" PRIu32 "\n", this->shrinesRestored);
	printf("  oneShotChestsOpened              = %" PRIu32 "\n", this->oneShotChestsOpened);
	printf("  loreNotesCollected               = %" PRIu32 "\n", this->loreNotesCollected);
	printf("  greatestDamageInflicted          = %f\n", this->greatestDamageInflicted);
	printf("  lastHit                          = %f\n", this->lastHit);
	printf("  lastHitBy                        = %f\n", this->lastHitBy);
	printf("  greatestDamageReceived           = %f\n", this->greatestDamageReceived);
	printf("  survivalWaveTier                 = %" PRIu32 "\n", this->survivalWaveTier);
	printf("  greatestSurvivalScore            = %" PRIu32 "\n", this->greatestSurvivalScore);
	printf("  cooldownRemaining                = %" PRIu32 "\n", this->cooldownRemaining);
	printf("  cooldownTotal                    = %" PRIu32 "\n", this->cooldownTotal);
	printf("  v_length                         = %" PRIu32 "\n", this->v_length);
	for(int i = 0; i < v_length; i++){
		printf("  v[%i]:\n", i);
		printf("    v[%i].str = %s\n", i, v[i].str.c_str());
		printf("    v[%i].num = %" PRIu32 "\n", i, v[i].num);
	}
	printf("  shatteredRealmSouls              = %" PRIu32 "\n", this->shatteredRealmSouls);
	printf("  shatteredRealmEssence            = %" PRIu32 "\n", this->shatteredRealmEssence);
	printf("  difficultySkip                   = %" PRIu32 "\n", this->difficultySkip);
	printf("  unknown1                         = %" PRIu32 "\n", this->unknown1);
	printf("  unknown2                         = %" PRIu32 "\n", this->unknown2);

}

void trigger_tokens::read(gdc_file *gdc)
{
	block b;

	if (gdc->read_block_start(&b) != 10)
		throw std::runtime_error("Expected trigger_tokens read_block_start to return 10.");

	if (gdc->read_int() != 2) // version
		throw std::runtime_error("Expected trigger_tokens version to be 2.");

	for (unsigned i = 0; i < 3; i++)
	{
		tokens[i].read(gdc);
	}

	gdc->read_block_end(&b);

}

void trigger_tokens::write(gdc_file *gdc)
{
	block b;

	gdc->write_block_start(&b, 10);
	gdc->write_int(2); // version

	for (unsigned i = 0; i < 3; i++)
	{
		tokens[i].write(gdc);
	}

	gdc->write_block_end(&b);
}

void trigger_tokens::print()
{
	printf("trigger_tokens:\n");
	for(int i = 0; i < 3; i++){
		printf("  token %i:\n", i);
		for(int j = 0; j < this->tokens[i].size(); j++){
			printf("%s\n", this->tokens[i][j].c_str());
		}
	}
}

void item::read(gdc_file *gdc)
{
	baseName.read(gdc);
	prefixName.read(gdc);
	suffixName.read(gdc);
	modifierName.read(gdc);
	transmuteName.read(gdc);
	seed = gdc->read_int();
	componentName.read(gdc);
	relicBonus.read(gdc);
	componentSeed = gdc->read_int();
	augmentName.read(gdc);
	unknown = gdc->read_int();
	augmentSeed = gdc->read_int();
	var1 = gdc->read_int();
	stackCount = gdc->read_int();
}

void item::write(gdc_file *gdc)
{
	baseName.write(gdc);
	prefixName.write(gdc);
	suffixName.write(gdc);
	modifierName.write(gdc);
	transmuteName.write(gdc);
	gdc->write_int(seed);
	componentName.write(gdc);
	relicBonus.write(gdc);
	gdc->write_int(componentSeed);
	augmentName.write(gdc);
	gdc->write_int(unknown);
	gdc->write_int(augmentSeed);
	gdc->write_int(var1);
	gdc->write_int(stackCount);
}

void item::print(){
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
}

void uid::read(gdc_file *gdc)
{
	for (unsigned i = 0; i < 16; i++)
	{
		id[i] = gdc->read_byte();
	}
}

void uid::write(gdc_file *gdc)
{
	for (unsigned i = 0; i < 16; i++)
	{
		gdc->write_byte(id[i]);
	}
}

void uid::print()
{
	printf("uid contents:\n");
	for (int i = 0; i < 16; i++){
		printf("  %u\n", this->id[i]);
	}
}

void string::read(gdc_file *gdc)
{
	uint32_t len = gdc->read_int();

	clear();
	reserve(len);

	for (uint32_t i = 0; i < len; i++)
	{
		push_back(gdc->read_byte());
	}
}

void string::write(gdc_file *gdc)
{
	uint32_t len = size();
	const char *str = data();

	gdc->write_int(len);

	for (uint32_t i = 0; i < len; i++)
	{
		gdc->write_byte(str[i]);
	}
}

void wstring::read(gdc_file *gdc)
{
	uint32_t len = gdc->read_int();

	clear();
	reserve(len);

	for (uint32_t i = 0; i < len; i++)
	{
		wchar_t c = gdc->read_byte();
		c |= gdc->read_byte() << 8;
		push_back(c);
	}
}

void wstring::write(gdc_file *gdc)
{
	uint32_t len = size();
	const wchar_t *str = data();

	gdc->write_int(len);

	for (uint32_t i = 0; i < len; i++)
	{
		gdc->write_byte(str[i]);
		gdc->write_byte(str[i] >> 8);
	}
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <in file> <out file>\n<in file> should be a player.gdc file.", argv[0]);
		return 1;
	}

	gdc_file gdc;

	try
	{
		gdc.read(argv[1]);
	}
	catch (const std::exception &e)
	{
		printf("Error reading file: %s", e.what());
		return 1;
	}

	try
	{
		gdc.write(argv[2]);
	}
	catch (const std::exception &e)
	{
		printf("Error writing file: %s\n", e.what());
		return 1;
	}

	return 0;
}
