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
		Building* getBlacksmith(unsigned int teamNum);
		Building* getApothecary(unsigned int teamNum);
		CharacterController* getControllerForCharacter(unsigned int id);
		void addControllerForCharacter(CharacterController* controller);
		void addHome(Building* building);
		void addBlacksmith(Building* building);
		void addApothecary(Building* building);
		IListenerCallback* getLevelListener();
		unsigned int getPlayerGold();
		void changePlayerGold(int amount);
		bool isApothecaryBuilt();
		bool isBlacksmithBuilt();
		void setApothecaryBuilt(bool val);
		void setBlacksmithBuilt(bool val);
	private:
		LevelManager();
		LevelManager(SceneManager const&);
		LevelManager& operator=(SceneManager const&);
		~LevelManager();

		static LevelManager* instance;
		Level* level;
};

#endif
