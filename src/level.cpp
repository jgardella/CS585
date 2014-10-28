#include "level.hh"

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
		for(j = 0; j < keys->length(); j++)
		{
			// factory will automatically register actor with grid
			(void) CharacterFactory::get(key, (*positions->get(j))->x, (*positions->get(j))->y);
		}
	}		
}

int Level::getWorldWidth()
{
	return width;
}

int Level::getWorldHeight()
{
	return height;
}
