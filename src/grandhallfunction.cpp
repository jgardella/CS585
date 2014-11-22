#include "grandhallfunction.hh"

GrandHallFunction::GrandHallFunction(int spawnX, int spawnY) : BuildingFunction("grandhall")
{
	this->spawnX = spawnX;
	this->spawnY = spawnY;
}

bool GrandHallFunction::parseKeyPress(int key, int cursorX, int cursorY)
{
	switch(key)
	{
		case 'r':
			CharacterFactory::get("dwarf", spawnX, spawnY);
			return true;
	}
	return false;
}
