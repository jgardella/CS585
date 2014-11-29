#ifndef _ARMORFACTORY_HH_
#define _ARMORFACTORY_HH_

#include "armor.hh"
#include "armorinfo.hh"
#include "trie.hh"

class ArmorFactory
{
	public:
		static Armor* get(std::string name);
		static void addArmorInfo(std::string name, tArmorInfo* info);
	private:
		static Trie<tArmorInfo*>* armorInfos;
};

#endif
