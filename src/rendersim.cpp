#include "rendersim.hh"

void RenderSim::config(std::string gameConfigPath)
{
	unsigned int i;
	JSONObject* obj = (JSONObject*)*(JSONParser::parseFile(gameConfigPath)->get(0));
	Trie<JSONItem*>* trie = obj->getTrie();
	DynamicArray<JSONItem*>* configs = ((JSONArray*)trie->get("configs"))->getDynamicArray();
	for(i = 0; i < configs->length(); i++)
	{
		parseSubConfig((JSONObject*)*JSONParser::parseFile(((JSONPrimitive<std::string>*)*configs->get(0))->getPrimitive())->get(0));
	}
}

void RenderSim::parseSubConfig(JSONObject* configObject)
{
	Trie<JSONItem*>* trie = configObject->getTrie();
	if(((JSONPrimitive<std::string>*)*trie->get("key"))->getPrimitive().compare("level") == 0)
	{
			parseLevelConfig(trie);
	}
	else if(((JSONPrimitive<std::string>*)*trie->get("key"))->getPrimitive().compare("key") == 0)
	{
			parseRenderingConfig(trie);
	}
}

void RenderSim::parseLevelConfig(Trie<JSONItem*>* trie)
{
	tLevelInfo* levelInfo;
	int width, height;
	std::string defaultTile;
	width = ((JSONPrimitive<int>*)*trie->get("width"))->getPrimitive();
	height = ((JSONPrimitive<int>*)trie->get("height"))->getPrimitive();
	defaultTile = ((JSONPrimitive<std::string>*)trie->get("defaulttile"))->getPrimitive();
	levelInfo = new tLevelInfo(width, height, defaultTile);
	levelInfo->setPositions("tree", jsonArrayToPositionList(((JSONArray*)*trie->get("tree"))));
	levelInfo->setPositions("water", jsonArrayToPositionList(((JSONArray*)*trie->get("water"))));
	levelInfo->setPositions("mountain", jsonArrayToPositionList(((JSONArray*)*trie->get("mountain"))));
	levelInfo->setPositions("grass", jsonArrayToPositionList(((JSONArray*)*trie->get("grass"))));
	levelManager.loadLevel(*levelInfo);
}

DynamicArray<tPosition*>* RenderSim::jsonArrayToPositionList(JSONArray* array)
{
	DynamicArray<tPosition*>* positions = new DynamicArray<tPosition*>();
	DynamicArray<JSONItem*>* convertedArray = array->getDynamicArray();
	unsigned int i;
	for(i = 0; i < convertedArray->length(); i++)
	{
		positions->pushBack(new tPosition(((JSONPrimitive<int>*)((JSONObject*)*convertedArray->get(i))->getTrie()->get("x"))->getPrimitive(),
					((JSONPrimitive<int>*)((JSONObject*)*convertedArray->get(i))->getTrie()->get("y"))->getPrimitive()));
	}
	return positions;
}

void RenderSim::parseRenderingConfig(Trie<JSONItem*>* trie)
{
	unsigned int i = 0;
	DynamicArray<std::string>* keys = trie->getKeys();
	for(i = 0; i < keys->length(); i++)
	{
		tRenderInfo renderInfo;
		renderInfo.color = ((JSONPrimitive<std::string>*)*((JSONObject*)*trie->get(*keys->get(i)))->getTrie()->get("color"))->getPrimitive();
		renderInfo.character = ((JSONPrimitive<std::string>*)*((JSONObject*)*trie->get(*keys->get(i)))->getTrie()->get("character"))->getPrimitive();
		renderingConfig->add(*keys->get(i), renderInfo);
	}
}
