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
		case 'b':
			BuildingFactory::get("blacksmith", cursorX, cursorY, 0);
			return true;
		case 'a':
			BuildingFactory::get("apothecary", cursorX, cursorY, 0);
			return true;
	}
	return false;
}
