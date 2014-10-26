#include "levelmanager.hh"

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
