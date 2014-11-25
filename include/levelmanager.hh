#ifndef _LEVELMANAGER_HH_
#define _LEVELMANAGER_HH_

#include "levelinfo.hh"
#include "level.hh"
#include "irenderer.hh"
#include "building.hh"
#include "charactercontroller.hh"
#include "ilistenercallback.hh"

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
		Building* getHome(unsigned int teamNum);
		CharacterController* getControllerForCharacter(unsigned int id);
		void addControllerForCharacter(CharacterController* controller);
		void addHome(Building* building);
		IListenerCallback* getLevelListener();
		unsigned int getPlayerGold();
		void removePlayerGold(unsigned int amount);
	private:
		LevelManager();
		LevelManager(SceneManager const&);
		LevelManager& operator=(SceneManager const&);
		~LevelManager();

		static LevelManager* instance;
		Level level;
};

#endif
