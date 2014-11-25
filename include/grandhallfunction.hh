#ifndef _GRANDHALLFUNCTION_HH_
#define _GRANDHALLFUNCTION_HH_

#include "buildingfunction.hh"
#include "characterfactory.hh"
#include "buildingfactory.hh"

class GrandHallFunction : public BuildingFunction
{
	public:
		GrandHallFunction(int spawnX, int spawnY, Trie<double>* behavioralConfig);
		virtual bool parseKeyPress(int key, int cursorX, int cursorY);

	private:
		int spawnX, spawnY;
		Trie<double>* behavioralConfig;
};

#endif
