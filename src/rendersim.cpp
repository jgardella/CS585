#include "rendersim.hh"

void RenderSim::config(std::string gameConfigPath)
{
	unsigned int i;
	JSONObject obj = JSONParser.parseFile(gameConfigPath).get(0);
	Trie<JSONItem*>* trie = obj->getTrie();
	DynamicArray<JSONtem*>* configs = trie->get("configs")->getDynamicArray();
	for(i = 0; i < configs->length(); i++)
	{
		parseSubConfig(JSONParser.parseFile(configs->get(0)->getPrimitive()));
	}
}

void RenderSim::parseSubConfig(JSONObject* configObject)
{
	Trie<JSONItem*>* trie = configObject->getTree();
	switch(trie->get("key")->getPrimitive)
	{
		case "level":
			parseLevelConfig(trie);
			break;
		case "rendering":
			parseRenderingConfig(trie);
			break;
	}
}

void RenderSim::parseLevelConfig(Trie<JSONItem*> trie)
{
	LevelInfo* levelInfo;
	int width, height;
	std::string defaultTile;
	width = trie->get("width")->getPrimitive();
	height = trie->get("height")->getPrimitive();
	defaultTile = trie->get("defaulttile")->getPrimitive();
	levelInfo = new LevelInfo(width, height, defaultTile);
	levelInfo->setPositions("tree", jsonArrayToPositionList(trie->get("tree")));
	levelInfo->setPositions("water", jsonArrayToPositionList(trie->get("water")));
	levelInfo->setPositions("mountain", jsonArrayToPositionList(trie->get("mountain")));
	levelInfo->setPositions("grass", jsonArrayToPositionList(trie->get("grass")));
	levelManager->loadLevel(*levelInfo);
}

DynamicArray<tPosition*>* RenderSim::jsonArrayToPositionList(JSONArray* array)
{
	DynamicArray<tPostion*>* positions = new DynamicArray<tPosition*>();
	DynamicArray<JSONItem*>* convertedArray = array->getDynamicArray();
	unsigned int i;
	for(i = 0; i < convertedArray->length(); i++)
	{
		positions->pushBack(new tPosition(convertedArray->get(i)->get("x")->getPrimitive(),
					convertedArray->get(i)->get("y")->getPrimitive()));
	}
	return positions;
}

void RenderSim::parseRenderingConfig(Trie<JSONItem*>* trie)
{
	unsigned int i = 0;
	DynamicArray<std::string>* keys = trie->getKeys();
	for(i = 0; i < keys->length(); i++)
	{
		sRenderInfo renderInfo;
		renderInfo.color = trie->get(keys->get(i))->get("color")->getPrimitive();
		renderInfo.character = trie->get(keys->get(i))->get("character")->getPrimitive();
		renderingConfig->add(keys->get(i), renderInfo);
	}
}
