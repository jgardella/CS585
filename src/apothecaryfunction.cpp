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
					return true;
				}
			}
			else if(level == 2)
			{
				if(LevelManager::getInstance()->getPlayerGold() >= *behavioralConfig->get("upgradetwocost"))
				{
					LevelManager::getInstance()->changePlayerGold((int)-*behavioralConfig->get("upgradetwocost"));
					behavioralConfig->add("level",  level + 1);
					return true;
				}
			}
			break;
	}
	return false;
}
