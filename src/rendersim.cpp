#include "rendersim.hh"

void RenderSim::run()
{
	std::clock_t startTime = clock(), finishTime = startTime;
	while(true)
	{
		startTime = clock();
		SceneManager::getInstance()->tick((float)(startTime - finishTime));
		finishTime = startTime;
	}	
}

void RenderSim::config(std::string gameConfigPath)
{
	unsigned int i;
	JSONObject* obj = (JSONObject*)*(JSONParser::parseFile(gameConfigPath)->get(0));
	Trie<JSONItem*>* trie = obj->getTrie();
	DynamicArray<JSONItem*>* configs = ((JSONArray*)trie->get("configs"))->getDynamicArray();
	SceneManager::getInstance()->addTickable(new RandomLocationCharacterSpawner(10, "orc")); 
	SceneManager::getInstance()->addTickable(new RandomLocationCharacterSpawner(10, "dwarf")); 
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
	else if(((JSONPrimitive<std::string>*)*trie->get("key"))->getPrimitive().compare("character") == 0)
	{
			parseCharacterConfig(trie);
	}
	else if(((JSONPrimitive<std::string>*)*trie->get("key"))->getPrimitive().compare("tile") == 0)
	{
		parseTileConfig(trie);
	}
}

void RenderSim::parseTileConfig(Trie<JSONItem*>* trie)
{
	tTileInfo* tileInfo = new tTileInfo();
	tileInfo->type = ((JSONPrimitive<std::string>*)*trie->get("type"))->getPrimitive();
	tileInfo->collides = ((JSONPrimitive<bool>*)*trie->get("collides"))->getPrimitive();
	TileFactory::addTileInfo(tileInfo->type, tileInfo);
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
	LevelManager::getInstance()->loadLevel(*levelInfo);
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

Trie<float>* RenderSim::jsonObjectToBehavioralConfig(JSONObject* object)
{
	unsigned int i;
	Trie<float>* behavioralConfig = new Trie<float>();
	Trie<JSONItem*>* trie = object->getTrie();
	DynamicArray<std::string>* keys = trie->getKeys();
	for(i = 0; i < keys->length(); i++)
	{
		behavioralConfig->add(*keys->get(i), ((JSONPrimitive<float>*)*trie->get(*keys->get(i)))->getPrimitive());
	}
	return behavioralConfig;
}

void RenderSim::parseCharacterConfig(Trie<JSONItem*>* trie)
{
	tCharacterInfo* charInfo = new tCharacterInfo();
	Trie<IState*>* stateMap = new Trie<IState*>();
	stateMap->add("attack", new AttackState(NULL, NULL)); // these will be initialized in
	stateMap->add("patrol", new PatrolState(NULL, NULL)); // the character factory
	charInfo->type = ((JSONPrimitive<std::string>*)*trie->get("type"))->getPrimitive();
	charInfo->behavioralConfig = jsonObjectToBehavioralConfig((JSONObject*)*trie->get("behavioralconfig"));
	charInfo->stateMap = stateMap;
	charInfo->startState = ((JSONPrimitive<std::string>*)*trie->get("startstate"))->getPrimitive();
	charInfo->health = ((JSONPrimitive<unsigned int>*)*trie->get("health"))->getPrimitive();
	CharacterFactory::addCharacterInfo(charInfo->type, charInfo);
}
