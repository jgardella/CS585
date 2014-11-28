#include "grandhallfunction.hh"

GrandHallFunction::GrandHallFunction(int spawnX, int spawnY, Trie<double>* behavioralConfig) : BuildingFunction("grandhall")
{
	this->spawnX = spawnX;
	this->spawnY = spawnY;
	this->behavioralConfig = behavioralConfig;
}

bool GrandHallFunction::parseKeyPress(int key, int cursorX, int cursorY)
{
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
				BuildingFactory::get("blacksmith", cursorX, cursorY, 0);
				LevelManager::getInstance()->changePlayerGold((int)-*behavioralConfig->get("blacksmithcost"));
				LevelManager::getInstance()->setBlacksmithBuilt(true);
				return true;
			}
			break;
		case 'a':
			if(LevelManager::getInstance()->getPlayerGold() >= *behavioralConfig->get("apothecarycost") && !LevelManager::getInstance()->isApothecaryBuilt())
			{
				BuildingFactory::get("apothecary", cursorX, cursorY, 0);
				LevelManager::getInstance()->changePlayerGold((int)-*behavioralConfig->get("apothecarycost"));
				LevelManager::getInstance()->setApothecaryBuilt(true);
				return true;
			}
			break;
	}
	return false;
}
