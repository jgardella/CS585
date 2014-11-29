#ifndef _WEAPON_HH_
#define _WEAPON_HH_

#include <string>

// enum for quality of good
typedef enum
{
	LESSER, NORMAL, MASTERWORK
} Quality;

class Weapon
{

	public:
		
		Weapon(std::string name, Quality quality, float chanceToHit, int damage);
		
		std::string getName();
		Quality getQuality();
		float getHitChance();
		int getDamage();


	private:
		std::string name;
		Quality quality;
		float chanceToHit;
		int damage;
};

#endif
