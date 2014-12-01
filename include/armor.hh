#ifndef _ARMOR_HH_
#define _ARMOR_HH_

#include <string>
#include "quality.hh"

class Armor
{

	public:
		
		Armor(std::string name, int quality, int defence, int blockChance);
		
		std::string getName();
		int getQuality();
		int getDefence();
		int getBlockChance();

	private:
		std::string name;
		int quality;
		int defence;
		int blockChance;
};

#endif
