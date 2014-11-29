#include "armor.hh"

Armor::Armor(std::string name, int quality, int defence)
{
	this->name = name;
	this->quality = quality;
	this->defence = defence;
}

std::string Armor::getName()
{
	return name;
}

int Armor::getQuality()
{
	return quality;
}

int Armor::getDefence()
{
	return defence;
}
