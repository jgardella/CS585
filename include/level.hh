#ifndef _LEVEL_HH_
#define _LEVEL_HH_

#include "levelinfo.hh"
#include "fixedgrid.hh"
#include "scenemanager.hh"
#include "characterfactory.hh"
#include "tilefactory.hh"

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
		std::string getDefaultTile();
	private:
		int width;
		int height;
		std::string defaultTile;

};

#endif
