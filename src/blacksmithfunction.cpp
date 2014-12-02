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
					MenuManager::getInstance()->setAlertString("Upgraded weaponsmith to level 2.");
					return true;
				}
				MenuManager::getInstance()->setAlertString("You don't have enough gold! (need " + std::to_string(*behavioralConfig->get("weaponupgradeonecost")) + " g)");
				return false;
			}
			else if(weaponLevel == 2)
			{
				if(LevelManager::getInstance()->getPlayerGold() >= *behavioralConfig->get("weaponupgradetwocost"))
				{
					LevelManager::getInstance()->changePlayerGold((int)-*behavioralConfig->get("weaponupgradetwocost"));
					behavioralConfig->add("weaponlevel",  weaponLevel + 1);
					MenuManager::getInstance()->setAlertString("Upgraded weaponsmith to level 3.");
					return true;
				}
				MenuManager::getInstance()->setAlertString("You don't have enough gold! (need " + std::to_string(*behavioralConfig->get("weaponupgradetwocost")) + " g)");
				return false;
			}
			MenuManager::getInstance()->setAlertString("Weaponsmith fully upgraded.");
			break;
		case 'a':
			armorLevel = *behavioralConfig->get("armorlevel");
			if(armorLevel == 1)
			{
				if(LevelManager::getInstance()->getPlayerGold() >= *behavioralConfig->get("armorupgradeonecost"))
				{
					LevelManager::getInstance()->changePlayerGold((int)-*behavioralConfig->get("armorupgradeonecost"));
					behavioralConfig->add("armorlevel",  armorLevel + 1);
					MenuManager::getInstance()->setAlertString("Upgraded armorer to level 2.");
					return true;
				}
				MenuManager::getInstance()->setAlertString("You don't have enough gold! (need " + std::to_string(*behavioralConfig->get("armorupgradeonecost")) + " g)");
				return false;
			}
			else if(armorLevel == 2)
			{
				if(LevelManager::getInstance()->getPlayerGold() >= *behavioralConfig->get("armorupgradetwocost"))
				{
					LevelManager::getInstance()->changePlayerGold((int)-*behavioralConfig->get("armorupgradetwocost"));
					behavioralConfig->add("armorlevel",  armorLevel + 1);
					MenuManager::getInstance()->setAlertString("Upgraded armorer to level 3.");
					return true;
				}
				MenuManager::getInstance()->setAlertString("You don't have enough gold! (need " + std::to_string(*behavioralConfig->get("armorupgradetwocost")) + " g)");
				return false;
			}
			MenuManager::getInstance()->setAlertString("Armorer fully upgraded.");
			break;
	}
	return false;
}
