#ifndef _TILEFACTORY_HH_
#define _TILEFACTORY_HH_

#include "tile.hh"
#include "scenemanager.hh"

class TileFactory
{
	public:
		// Creates a new tile of the given type and places it at the given coordinates in the world. Returns a reference to the actor.
		// Parameters:
		// std::string type - the type of the actor
		// int x - the x coordinate at which to instantiate the actor
		// int y - the y coordinate at which to instantiate the actor
		static Tile* get(std::string type, int x, int y);
};

#endif
