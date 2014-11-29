#include "weaponfactory.hh"

Trie<tWeaponInfo*>* WeaponFactory::weaponInfos = new Trie<tWeaponInfo*>();

Weapon* WeaponFactory::get(std::string name)
{
	tWeaponInfo* info = *weaponInfos->get(name);

	return new Weapon(info->name, info->quality, info->hitChance, info->damage);
}

void WeaponFactory::addWeaponInfo(std::string name, tWeaponInfo* info)
{
	weaponInfos->add(name, info);
}
