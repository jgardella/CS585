#include "weapon.hh"

Weapon::Weapon(std::string name, int quality, int chanceToHit, int damage)
{
	this->name = name;
	this->quality = quality;
	this->chanceToHit = chanceToHit;
	this->damage = damage;
}

std::string Weapon::getName()
{
	return name;
}

int Weapon::getQuality()
{
	return quality;
}

int Weapon::getHitChance()
{
	return chanceToHit;
}

int Weapon::getDamage()
{
	return damage;
}
