#include "levelmanager.hh"

LevelManager* LevelManager::instance;

LevelManager::LevelManager()
{
	
}

LevelManager* LevelManager::getInstance()
{
	if(instance == NULL)
	{
		instance = new LevelManager();
	}
	return instance;
}

void LevelManager::loadLevel(tLevelInfo info)
{
	level = Level(info);
}

void LevelManager::tick(float dt)
{
	level.tick(dt);
}

int LevelManager::getWorldWidth()
{
	return level.getWorldWidth();
}

int LevelManager::getWorldHeight()
{
	return level.getWorldHeight();
}

std::string LevelManager::getDefaultTile()
{
	return level.getDefaultTile();
}

Building* LevelManager::getHome(unsigned int teamNum)
{
	return level.getHome(teamNum);
}

CharacterController* LevelManager::getControllerForCharacter(unsigned int id)
{
	return level.getControllerForCharacter(id);
}

void LevelManager::addControllerForCharacter(CharacterController* controller)
{
	level.addControllerForCharacter(controller);
}

IListenerCallback* LevelManager::getLevelListener()
{
	return level.getListener();
}

void LevelManager::addHome(Building* building)
{
	level.addHome(building);
}

unsigned int LevelManager::getPlayerGold()
{
	return level.getPlayerGold();
}

void LevelManager::removePlayerGold(unsigned int amount)
{
	level.removePlayerGold(amount);
}
