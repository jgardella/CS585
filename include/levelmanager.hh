#ifndef _LEVELMANAGER_HH_
#define _LEVELMANAGER_HH_

#include "levelinfo.hh"
#include "level.hh"
#include "irenderer.hh"

class LevelManager
{
	public:
		// Loads the level specified by the given info object.
		// Parameters:
		// LevelInfo info - the info object for the level to load
		void loadLevel(tLevelInfo info);
		
		void tick(float dt);

		void setRenderer(IRenderer* renderer);
		
		static LevelManager* getInstance();
		
		int getWorldWidth();
		int getWorldHeight();
		std::string getDefaultTile();
	private:
		LevelManager();
		LevelManager(SceneManager const&);
		LevelManager& operator=(SceneManager const&);
		~LevelManager();

		static LevelManager* instance;
		Level level;
};

#endif
