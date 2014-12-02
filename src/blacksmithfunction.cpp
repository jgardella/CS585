#include "blacksmithfunction.hh"

BlacksmithFunction::BlacksmithFunction(Trie<double>* behavioralConfig) : BuildingFunction("blacksmith")
{
	this->behavioralConfig = behavioralConfig;
}

bool BlacksmithFunction::parseKeyPress(int key, int cursorX, int cursorY)
{
	int armorLevel, weaponLevel;
	switch(key)
	{
		case 'w':
			weaponLevel = *behavioralConfig->get("weaponlevel");
			if(weaponLevel == 1)
			{
				if(LevelManager::getInstance()->getPlayerGold() >= *behavioralConfig->get("weaponupgradeonecost"))
				{
					LevelManager::getInstance()->changePlayerGold((int)-*behavioralConfig->get("weaponupgradeonecost"));
					behavioralConfig->add("weaponlevel",  weaponLevel + 1);
					return true;
				}
			}
			else if(weaponLevel == 2)
			{
				if(LevelManager::getInstance()->getPlayerGold() >= *behavioralConfig->get("weaponupgradetwocost"))
				{
					LevelManager::getInstance()->changePlayerGold((int)-*behavioralConfig->get("weaponupgradetwocost"));
					behavioralConfig->add("weaponlevel",  weaponLevel + 1);
					return true;
				}
			}
			break;
		case 'a':
			armorLevel = *behavioralConfig->get("armorlevel");
			if(armorLevel == 1)
			{
				if(LevelManager::getInstance()->getPlayerGold() >= *behavioralConfig->get("armorupgradeonecost"))
				{
					LevelManager::getInstance()->changePlayerGold((int)-*behavioralConfig->get("armorupgradeonecost"));
					behavioralConfig->add("armorlevel",  armorLevel + 1);
					return true;
				}
			}
			else if(armorLevel == 2)
			{
				if(LevelManager::getInstance()->getPlayerGold() >= *behavioralConfig->get("armorupgradetwocost"))
				{
					LevelManager::getInstance()->changePlayerGold((int)-*behavioralConfig->get("armorupgradetwocost"));
					behavioralConfig->add("armorlevel",  armorLevel + 1);
					return true;
				}
			}
			break;
	}
	return false;
}
