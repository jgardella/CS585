#include "level.hh"

Level::Level(tLevelInfo level)
{
	unsigned int i, j;
	DynamicArray<tPosition*>* positions;
	DynamicArray<std::string>* keys = level.positionTrie->getKeys();
	characterControllers = new DynamicArray<CharacterController*>();
	teamHomes = new DynamicArray<Building*>();
	teamBlacksmiths = new DynamicArray<Building*>();
	teamApothecaries = new DynamicArray<Building*>();
	std::string key;

	width = level.width;
	height = level.height;
	defaultTile = level.defaultTile;
	playerGold = level.initialGold;
	blacksmithBuilt = false;
	apothecaryBuilt = false;
	SceneManager::getInstance()->setGraph(new FixedGrid(width, height));
	
	onDeathEvent.setInstance(this);

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
	unsigned int i;
	for(i = 0; i < teamHomes->length(); i++)
	{
		if((*teamHomes->get(i))->getTeamNumber() == teamNum)
		{
			return *teamHomes->get(i);
		}
	}
	return NULL;
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
	removeControllerForCharacter(event->getVictim()->getID());
	MenuManager::getInstance()->setAlertString(event->getVictim()->getType() + " #" + std::to_string(event->getVictim()->getID()) + " is slain by " + event->getAttacker()->getType() + " #" + std::to_string(event->getAttacker()->getID()) + ".");
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
	DEBUG_LOG("LEVEL", "Changing player gold by amount: " + std::to_string(amount));
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

bool Level::isApothecaryBuilt()
{
	return apothecaryBuilt;
}

bool Level::isBlacksmithBuilt()
{
	return blacksmithBuilt;
}

void Level::setApothecaryBuilt(bool val)
{
	apothecaryBuilt = val;
}

void Level::setBlacksmithBuilt(bool val)
{
	blacksmithBuilt = val;
}

Building* Level::getBlacksmith(unsigned int teamNum)
{
	unsigned int i;
	for(i = 0; i < teamBlacksmiths->length(); i++)
	{
		if((*teamBlacksmiths->get(i))->getTeamNumber() == teamNum)
		{
			return *teamBlacksmiths->get(i);
		}
	}
	return NULL;
}

void Level::addBlacksmith(Building* building)
{
	teamBlacksmiths->pushBack(building);
}

Building* Level::getApothecary(unsigned int teamNum)
{
	unsigned int i;
	for(i = 0; i < teamApothecaries->length(); i++)
	{
		if((*teamApothecaries->get(i))->getTeamNumber() == teamNum)
		{
			return *teamApothecaries->get(i);
		}
	}
	return NULL;
}

void Level::addApothecary(Building* building)
{
	teamApothecaries->pushBack(building);
}
