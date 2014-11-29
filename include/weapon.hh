#ifndef _WEAPON_HH_
#define _WEAPON_HH_

#include <string>
#include "quality.hh"

class Weapon
{

	public:
		
		Weapon(std::string name, int quality, double chanceToHit, int damage);
		
		std::string getName();
		int getQuality();
		double getHitChance();
		int getDamage();


	private:
		std::string name;
		int quality;
		double chanceToHit;
		int damage;
};

#endif
