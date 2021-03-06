#ifndef _RENDERSIM_HH_
#define _RENDERSIM_HH_

#include "jsonparser.hh"
#include "jsonobject.hh"
#include "jsonarray.hh"
#include "jsonitem.hh"
#include "jsonprimitive.hh"
#include "trie.hh"
#include "dynamicarray.hh"
#include "sposition.hh"
#include "levelmanager.hh"
#include "characterinfo.hh"
#include "patrolstate.hh"
#include "attackstate.hh"
#include "tileinfo.hh"
#include "randomlocationcharacterspawner.hh"
#include "debug.hh"
#include "renderinfo.hh"
#include "asciirenderer.hh"
#include "worldcontroller.hh"
#include "buildingfactory.hh"
#include "buildinginfo.hh"
#include "menumanager.hh"
#include "weaponfactory.hh"
#include "weaponinfo.hh"
#include "armorfactory.hh"
#include "armorinfo.hh"
#include "healthpotionfactory.hh"
#include "healthpotioninfo.hh"

class RenderSim 
{
	public:
		// Loads the game config at the specified path.
		// Parameters:
		// std::string gameConfigPath - path to the game config json file
		void config(std::string gameConfigPath);

		// Initiates the game.
		void run();

	private:
		ASCIIRenderer* renderer;
		WorldController* worldController;

		void parseSubConfig(JSONObject* configObject);

		void parseLevelConfig(Trie<JSONItem*>* trie);

		DynamicArray<tPosition*>* jsonArrayToPositionList(JSONArray* array);
		
		Trie<double>* jsonObjectToBehavioralConfig(JSONObject* object);

		DynamicArray<int>* jsonArrayToLevelList(JSONArray* array);
		
		Trie<IState*>* getStateMap(std::string type);
		
		void parseCharacterConfig(Trie<JSONItem*>* trie);
		
		void parseTileConfig(Trie<JSONItem*>* trie);

		void parseRenderConfig(Trie<JSONItem*>* trie);
		
		void parseBuildingConfig(Trie<JSONItem*>* trie);

		void parseMenuConfig(Trie<JSONItem*>* trie);
		
		void parseWeaponConfig(Trie<JSONItem*>* trie);
		
		void parseArmorConfig(Trie<JSONItem*>* trie);
		
		void parseHealthPotionConfig(Trie<JSONItem*>* trie);
};

#endif
