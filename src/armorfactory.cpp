#include "armorfactory.hh"

Trie<tArmorInfo*>* ArmorFactory::armorInfos = new Trie<tArmorInfo*>();

Armor* ArmorFactory::get(std::string name)
{
	tArmorInfo* info = *armorInfos->get(name);

	return new Armor(info->name, info->quality, info->defence, info->blockChance);
}

void ArmorFactory::addArmorInfo(std::string name, tArmorInfo* info)
{
	armorInfos->add(name, info);
}
