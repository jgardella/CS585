#include "healthpotion.hh"

HealthPotion::HealthPotion(std::string name, int quality, int healValue)
{
	this->name = name;
	this->quality = quality;
	this->healValue = healValue;
}

std::string HealthPotion::getName()
{
	return name;
}

int HealthPotion::getQuality()
{
	return quality;
}

int HealthPotion::getHealValue()
{
	return healValue;
}
