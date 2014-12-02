#include "apothecaryfunction.hh"

ApothecaryFunction::ApothecaryFunction(Trie<double>* behavioralConfig) : BuildingFunction("grandhall")
{
	this->behavioralConfig = behavioralConfig;
}

bool ApothecaryFunction::parseKeyPress(int key, int cursorX, int cursorY)
{
	int level;
	switch(key)
	{
		case 'u':
			level = *behavioralConfig->get("level");
			if(level == 1)
			{
				if(LevelManager::getInstance()->getPlayerGold() >= *behavioralConfig->get("upgradeonecost"))
				{
					LevelManager::getInstance()->changePlayerGold((int)-*behavioralConfig->get("upgradeonecost"));
					behavioralConfig->add("level",  level + 1);
					MenuManager::getInstance()->setAlertString("Upgraded apothecary to level 2.");
					return true;
				}
				MenuManager::getInstance()->setAlertString("You don't have enough gold! (need " + std::to_string(*behavioralConfig->get("upgradeonecost")) + " g)");
			}
			else if(level == 2)
			{
				if(LevelManager::getInstance()->getPlayerGold() >= *behavioralConfig->get("upgradetwocost"))
				{
					LevelManager::getInstance()->changePlayerGold((int)-*behavioralConfig->get("upgradetwocost"));
					behavioralConfig->add("level",  level + 1);
					MenuManager::getInstance()->setAlertString("Upgraded apothecary to level 3.");
					return true;
				}
				MenuManager::getInstance()->setAlertString("You don't have enough gold! (need " + std::to_string(*behavioralConfig->get("upgradetwocost")) + " g)");
			}
			else
			{
				MenuManager::getInstance()->setAlertString("Apothecary is fully upgraded.");
			}
			break;
	}
	return false;
}
