#ifndef _WEAPONFACTORY_HH_
#define _WEAPONFACTORY_HH_

#include "weapon.hh"
#include "weaponinfo.hh"
#include "trie.hh"

class WeaponFactory
{
	public:
		static Weapon* get(std::string name);
		static void addWeaponInfo(std::string name, tWeaponInfo* info);
	private:
		static Trie<tWeaponInfo*>* weaponInfos;
};

#endif
