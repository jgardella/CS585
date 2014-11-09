#include "level.hh"

Level::Level()
{

}

Level::Level(tLevelInfo level)
{
	unsigned int i, j;
	DynamicArray<tPosition*>* positions;
	DynamicArray<std::string>* keys = level.positionTrie->getKeys();
	std::string key;

	width = level.width;
	height = level.height;
	defaultTile = level.defaultTile;
	SceneManager::getInstance()->setGraph(new FixedGrid(width, height));

	for(i = 0; i < keys->length(); i++)
	{
		key = *keys->get(i);
		positions = *level.positionTrie->get(key);
		for(j = 0; j < positions->length(); j++)
		{
			if(key.compare("orc") == 0 || key.compare("dwarf") == 0)
			{
				(void) CharacterFactory::get(key, (*positions->get(j))->x, (*positions->get(j))->y);
			}
			else if(key.compare("grandhall") == 0)
			{
				(void) BuildingFactory::get(key, (*positions->get(j))->x, (*positions->get(j))->y, 0);
			}
			else
			{
				DEBUG_LOG("LEVEL", "Getting tile at position (" + std::to_string((*positions->get(j))->x) + ", " + std::to_string((*positions->get(j))->y) + ").");
				(void) TileFactory::get(key, (*positions->get(j))->x, (*positions->get(j))->y);
			}
		}
	}

}

void Level::tick(float dt)
{
}

int Level::getWorldWidth()
{
	return width;
}

int Level::getWorldHeight()
{
	return height;
}

std::string Level::getDefaultTile()
{
	return defaultTile;
}

Building* Level::getHome(unsigned int teamNum)
{
	return *teamHomes->get(teamNum);
}
