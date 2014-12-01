#include "armor.hh"

Armor::Armor(std::string name, int quality, int defence, int blockChance)
{
	this->name = name;
	this->quality = quality;
	this->defence = defence;
	this->blockChance = blockChance;
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

int Armor::getBlockChance()
{
	return blockChance;
}
