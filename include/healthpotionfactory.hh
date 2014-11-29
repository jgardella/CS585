#ifndef _HEALTHPOTIONFACTORY_HH_
#define _HEALTHPOTIONFACTORY_HH_

#include "healthpotion.hh"
#include "healthpotioninfo.hh"
#include "trie.hh"

class HealthPotionFactory
{
	public:
		static HealthPotion* get(std::string name);
		static void addHealthPotionInfo(std::string name, tHealthPotionInfo* info);
	private:
		static Trie<tHealthPotionInfo*>* healthPotionInfos;
};

#endif
