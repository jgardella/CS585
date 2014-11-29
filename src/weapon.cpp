#include "weapon.hh"

Weapon::Weapon(std::string name, Quality quality, float chanceToHit, int damage)
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

Quality Weapon::getQuality()
{
	return quality;
}

float Weapon::getHitChance()
{
	return chanceToHit;
}

int Weapon::getDamage()
{
	return damage;
}
