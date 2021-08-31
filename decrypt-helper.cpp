#include <vector>
#include <string>
#include <stdint.h>
#include <inttypes.h>
#include "decrypt-helper.h"


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

void stash_item::print()
{
	this->item::print();
	printf("      x = %f\n", this->x);
	printf("      y = %f\n", this->y);
}

void stash_tab::print()
{
	printf("  stash_tab:\n");
	printf("    width     = %" PRIu32 "\n", width);
	printf("    height    = %" PRIu32 "\n", height);
	for(int i = 0; i < this->items.size(); i++){
		this->items[i].print();
	}
}

file::file(const char *name, const char *mode)
{
	fp = fopen(name, mode);
}

file::~file()
{
	if (fp) fclose(fp);
}