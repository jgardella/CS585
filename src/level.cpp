#include "level.hh"

Level::Level()
{
}

Level::Level(tLevelInfo level)
{
	unsigned int i, j;
	DynamicArray<tPosition*>* positions;
	DynamicArray<std::string>* keys = level.positionTrie->getKeys();
	characterControllers = new DynamicArray<CharacterController*>();
	teamHomes = new DynamicArray<Building*>();
	std::string key;

	width = level.width;
	height = level.height;
	defaultTile = level.defaultTile;
	playerGold = level.initialGold;
	SceneManager::getInstance()->setGraph(new FixedGrid(width, height));

	for(i = 0; i < keys->length(); i++)
	{
		key = *keys->get(i);
		positions = *level.positionTrie->get(key);
		for(j = 0; j < positions->length(); j++)
		{
			DEBUG_LOG("LEVEL", "Getting tile at position (" + std::to_string((*positions->get(j))->x) + ", " + std::to_string((*positions->get(j))->y) + ").");
			(void) TileFactory::get(key, (*positions->get(j))->x, (*positions->get(j))->y);
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

void Level::addHome(Building* building)
{
	teamHomes->pushBack(building);
}

void Level::addControllerForCharacter(CharacterController* controller)
{
	characterControllers->pushBack(controller);
}

CharacterController* Level::getControllerForCharacter(unsigned int id)
{
	unsigned int i;
	for(i = 0; i < characterControllers->length(); i++)
	{
		if((*characterControllers->get(i))->getID() == id)
		{
			return *characterControllers->get(i);
		}
	}
	return NULL;
}

void Level::removeControllerForCharacter(unsigned int id)
{
	unsigned int i;
	for(i = 0; i < characterControllers->length(); i++)
	{
		if((*characterControllers->get(i))->getID() == id)
		{
			characterControllers->remove(i);
			return;
		}
	}
}

void Level::processDeathEvent(DeathEvent* event)
{
	event->getAttacker()->setGold(event->getVictim()->getGold() + event->getAttacker()->getGold());
	removeControllerForCharacter(event->getAttacker()->getID());
}

IListenerCallback* Level::getListener()
{
	return &onDeathEvent;
}

unsigned int Level::getPlayerGold()
{
	return playerGold;
}

void Level::changePlayerGold(int amount)
{
	if(amount < 0)
	{
		if(-amount <= (int)playerGold)
		{
			playerGold += amount;
		}
	}
	else
	{
		playerGold += amount;
	}
}
