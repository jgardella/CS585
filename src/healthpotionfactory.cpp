#include "healthpotionfactory.hh"

Trie<tHealthPotionInfo*>* HealthPotionFactory::healthPotionInfos = new Trie<tHealthPotionInfo*>();

HealthPotion* HealthPotionFactory::get(std::string name)
{
	tHealthPotionInfo* info = *healthPotionInfos->get(name);

	return new HealthPotion(info->name, info->quality, info->healValue);
}

void HealthPotionFactory::addHealthPotionInfo(std::string name, tHealthPotionInfo* info)
{
	healthPotionInfos->add(name, info);
}
