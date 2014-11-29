#ifndef _HEALTHPOTIONINFO_HH_
#define _HEALTHPOTIONINFO_HH_

#include "quality.hh"
#include <string>

typedef struct sHealthPotionInfo
{
	std::string name;
	int quality;
	int healValue;
} tHealthPotionInfo;

#endif
