#ifndef _WEAPON_HH_
#define _WEAPON_HH_

#include <string>
#include "quality.hh"

class Weapon
{

	public:
		
		Weapon(std::string name, int quality, float chanceToHit, int damage);
		
		std::string getName();
		int getQuality();
		float getHitChance();
		int getDamage();


	private:
		std::string name;
		int quality;
		float chanceToHit;
		int damage;
};

#endif
