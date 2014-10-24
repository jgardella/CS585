#ifndef _LEVELMANAGER_HH_
#define _LEVELMANAGER_HH_

#include "levelinfo.hh"
#include "level.hh"

class LevelManager
{
	public:
		// Loads the level specified by the given info object.
		// Parameters:
		// LevelInfo info - the info object for the level to load
		void loadLevel(LevelInfo info);
		
		int getWorldWidth();
		int getWorldHeight();
	private:
		Level level;
};

#endif
