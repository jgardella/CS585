#include "grandhallfunction.hh"

GrandHallFunction::GrandHallFunction(int spawnX, int spawnY, Trie<double>* behavioralConfig) : BuildingFunction("grandhall")
{
	this->spawnX = spawnX;
	this->spawnY = spawnY;
	this->behavioralConfig = behavioralConfig;
}

bool GrandHallFunction::parseKeyPress(int key, int cursorX, int cursorY)
{
	int level;
	switch(key)
	{
		case 'r':
			if(LevelManager::getInstance()->getPlayerGold() >= *behavioralConfig->get("recruitcost"))
			{
				CharacterFactory::get("dwarf", spawnX, spawnY);
				LevelManager::getInstance()->changePlayerGold((int)-*behavioralConfig->get("recruitcost"));
				MenuManager::getInstance()->setAlertString("Recruited new dwarf.");
				return true;
			}
			MenuManager::getInstance()->setAlertString("You don't have enough gold! (need " + std::to_string(*behavioralConfig->get("recruitcost")) + " g)");
			break;
		case 'b':
			if(!LevelManager::getInstance()->isBlacksmithBuilt())
			{
				if(LevelManager::getInstance()->getPlayerGold() >= *behavioralConfig->get("blacksmithcost"))
				{
					LevelManager::getInstance()->addBlacksmith(BuildingFactory::get("blacksmith", cursorX, cursorY, 0));
					LevelManager::getInstance()->changePlayerGold((int)-*behavioralConfig->get("blacksmithcost"));
					LevelManager::getInstance()->setBlacksmithBuilt(true);
					MenuManager::getInstance()->setAlertString("Built blacksmith.");
					return true;
				}
				MenuManager::getInstance()->setAlertString("You don't have enough gold! (need " + std::to_string(*behavioralConfig->get("blacksmithcost")) + " g)");
				return false;
			}
			MenuManager::getInstance()->setAlertString("Blacksmith already built.");
			break;
		case 'a':
			if(!LevelManager::getInstance()->isApothecaryBuilt())
			{
				if(LevelManager::getInstance()->getPlayerGold() >= *behavioralConfig->get("apothecarycost"))
				{
					LevelManager::getInstance()->addApothecary(BuildingFactory::get("apothecary", cursorX, cursorY, 0));
					LevelManager::getInstance()->changePlayerGold((int)-*behavioralConfig->get("apothecarycost"));
					LevelManager::getInstance()->setApothecaryBuilt(true);
					MenuManager::getInstance()->setAlertString("Built apothecary.");
					return true;
				}
				MenuManager::getInstance()->setAlertString("You don't have enough gold! (need " + std::to_string(*behavioralConfig->get("apothecarycost")) + " g)");
				return false;
			}
			MenuManager::getInstance()->setAlertString("Apothecary already built.");
			break;
		case 'u':
			level = *behavioralConfig->get("level");
			if(level == 1)
			{
				if(LevelManager::getInstance()->getPlayerGold() >= *behavioralConfig->get("upgradeonecost"))
				{
					LevelManager::getInstance()->changePlayerGold((int)-*behavioralConfig->get("upgradeonecost"));
					behavioralConfig->add("level",  level + 1);
					MenuManager::getInstance()->setAlertString("Upgraded grand hall to level 2.");
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
					MenuManager::getInstance()->setAlertString("Upgraded grand hall to level 3.");
					return true;
				}
				MenuManager::getInstance()->setAlertString("You don't have enough gold! (need " + std::to_string(*behavioralConfig->get("upgradetwocost")) + " g)");
			}
			break;
	}
	return false;
}
