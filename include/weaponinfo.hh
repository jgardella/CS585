#ifndef _WEAPONINFO_HH_
#define _WEAPONINFO_HH_

#include "quality.hh"
#include <string>

typedef struct sWeaponInfo
{
	std::string name;
	int quality;
	int hitChance;
	int damage;
} tWeaponInfo;

#endif
