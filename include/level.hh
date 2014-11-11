#ifndef _LEVEL_HH_
#define _LEVEL_HH_

#include "levelinfo.hh"
#include "fixedgrid.hh"
#include "scenemanager.hh"
#include "characterfactory.hh"
#include "tilefactory.hh"
#include "statemachine.hh"
#include "building.hh"
#include "buildingfactory.hh"
#include "charactercontroller.hh"

class Level : public ITickable
{
	public:
		Level();
		
		// Constructs a level with a world of the given width and height.
		// Parameters:
		// int width - the width of the world
		// int height - the height of the world
		Level(tLevelInfo level);
		
		void tick(float dt);
		
		int getWorldWidth();
		int getWorldHeight();
		Building* getHome(unsigned int teamNum);
		std::string getDefaultTile();
		CharacterController* getControllerForCharacter(unsigned int id);
		void addControllerForCharacter(unsigned int id, CharacterController* controller);
	private:
		int width;
		int height;
		std::string defaultTile;
		DynamicArray<Building*>* teamHomes;
		Trie<CharacterController*>* characterControllers;
};

#endif
