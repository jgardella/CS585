#ifndef _GRANDHALLFUNCTION_HH_
#define _GRANDHALLFUNCTION_HH_

#include "buildingfunction.hh"
#include "characterfactory.hh"

class GrandHallFunction : public BuildingFunction
{
	public:
		GrandHallFunction(int spawnX, int spawnY);
		virtual bool parseKeyPress(int key, int cursorX, int cursorY);

	private:
		int spawnX, spawnY;
};

#endif
