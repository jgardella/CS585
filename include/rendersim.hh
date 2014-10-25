#ifndef _RENDERSIM_HH_
#define _RENDERSIM_HH_

#include "jsonparser.hh"
#include "jsonobject.hh"
#include "jsonarray.hh"
#include "jsonitem.hh"
#include "trie.hh"
#include "dynamicarray.hh"

typedef struct sRenderInfo
{
	std::string color;
	std::string character;
} tRenderInfo;

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
		LevelManager levelManager;
		Trie<tRenderInfo*>* renderingConfig;

		void parseSubConfig(JSONObject* configObject);

		void parseLevelConfig(Trie<JSONItem*> trie);

		DynamicArray<Position*>* jsonArrayToPositionList(JSONArray* array);

		void parseRenderingConfig(Trie<JSONItem*>* trie);

};

#endif
