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
				return true;
			}
			break;
		case 'b':
			if(LevelManager::getInstance()->getPlayerGold() >= *behavioralConfig->get("blacksmithcost") && !LevelManager::getInstance()->isBlacksmithBuilt())
			{
				LevelManager::getInstance()->addBlacksmith(BuildingFactory::get("blacksmith", cursorX, cursorY, 0));
				LevelManager::getInstance()->changePlayerGold((int)-*behavioralConfig->get("blacksmithcost"));
				LevelManager::getInstance()->setBlacksmithBuilt(true);
				return true;
			}
			break;
		case 'a':
			if(LevelManager::getInstance()->getPlayerGold() >= *behavioralConfig->get("apothecarycost") && !LevelManager::getInstance()->isApothecaryBuilt())
			{
				LevelManager::getInstance()->addApothecary(BuildingFactory::get("apothecary", cursorX, cursorY, 0));
				LevelManager::getInstance()->changePlayerGold((int)-*behavioralConfig->get("apothecarycost"));
				LevelManager::getInstance()->setApothecaryBuilt(true);
				return true;
			}
			break;
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
