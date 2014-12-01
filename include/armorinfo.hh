#ifndef _ARMORINFO_HH_
#define _ARMORINFO_HH_

#include "quality.hh"
#include <string>

typedef struct sArmorInfo
{
	std::string name;
	int quality;
	int defence;
	int blockChance;
} tArmorInfo;

#endif
