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

int LevelManager::getWorldWidth()
{
	return level.getWorldWidth();
}

int LevelManager::getWorldHeight()
{
	return level.getWorldHeight();
}
