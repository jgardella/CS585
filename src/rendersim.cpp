#include "rendersim.hh"

void RenderSim::run()
{
	std::clock_t startTime = clock(), finishTime = startTime;
	DEBUG_LOG("RENDERSIM", "Starting simulation.");
	while(true)
	{
		startTime = clock();
		SceneManager::getInstance()->tick((float)(startTime - finishTime));
		finishTime = startTime;
	}	
}

void RenderSim::config(std::string gameConfigPath)
{
	DEBUG_LOG("RENDERSIM", "Initiating game config.");
	unsigned int i;
	std::string subconfigPath;
	DEBUG_LOG("RENDERSIM", "Parsing game config file.");
	JSONObject* obj = (JSONObject*)*(JSONParser::parseFile(gameConfigPath)->get(0));
	DEBUG_LOG("RENDERSIM", "Getting Trie from game config JSON object.");
	Trie<JSONItem*>* trie = obj->getTrie();
	DEBUG_LOG("RENDERSIM", "Getting array of config files.");
	DynamicArray<JSONItem*>* configs = ((JSONArray*)*trie->get("configs"))->getDynamicArray();
	DEBUG_LOG("RENDERSIM", "Creating orc spawner.");
	SceneManager::getInstance()->addTickable(new RandomLocationCharacterSpawner(10, "orc")); 
	DEBUG_LOG("RENDERSIM", "Creating dwarf spawner.");
	SceneManager::getInstance()->addTickable(new RandomLocationCharacterSpawner(10, "dwarf")); 
	DEBUG_LOG("RENDERSIM", "Parsing sub configs.");
	for(i = 0; i < configs->length(); i++)
	{
		subconfigPath = ((JSONPrimitive<std::string>*)*configs->get(i))->getPrimitive();
		DEBUG_LOG("RENDERSIM", "Parsing sub config at path: \"" + subconfigPath + "\".");
		parseSubConfig((JSONObject*)*JSONParser::parseFile(subconfigPath)->get(0));
	}
}

void RenderSim::parseSubConfig(JSONObject* configObject)
{
	DEBUG_LOG("RENDERSIM", "Parsing sub config.");
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
	DEBUG_LOG("RENDERSIM", "Parsing tile config.");
	tTileInfo* tileInfo = new tTileInfo();
	tileInfo->type = ((JSONPrimitive<std::string>*)*trie->get("type"))->getPrimitive();
	tileInfo->collides = ((JSONPrimitive<bool>*)*trie->get("collides"))->getPrimitive();
	TileFactory::addTileInfo(tileInfo->type, tileInfo);
}

void RenderSim::parseLevelConfig(Trie<JSONItem*>* trie)
{
	DEBUG_LOG("RENDERSIM", "Parsing level config.");
	tLevelInfo* levelInfo;
	int width, height;
	std::string defaultTile;
	width = ((JSONPrimitive<int>*)*trie->get("width"))->getPrimitive();
	height = ((JSONPrimitive<int>*)*trie->get("height"))->getPrimitive();
	defaultTile = ((JSONPrimitive<std::string>*)*trie->get("defaulttile"))->getPrimitive();
	levelInfo = new tLevelInfo(width, height, defaultTile);
	levelInfo->setPositions("tree", jsonArrayToPositionList(((JSONArray*)*trie->get("tree"))));
	levelInfo->setPositions("water", jsonArrayToPositionList(((JSONArray*)*trie->get("water"))));
	levelInfo->setPositions("mountain", jsonArrayToPositionList(((JSONArray*)*trie->get("mountain"))));
	levelInfo->setPositions("grass", jsonArrayToPositionList(((JSONArray*)*trie->get("grass"))));
	LevelManager::getInstance()->loadLevel(*levelInfo);
}

DynamicArray<tPosition*>* RenderSim::jsonArrayToPositionList(JSONArray* array)
{
	DEBUG_LOG("RENDERSIM", "Converting JSON Array to Dynamic Array of positions.");
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

Trie<double>* RenderSim::jsonObjectToBehavioralConfig(JSONObject* object)
{
	DEBUG_LOG("RENDERSIM", "Converting JSON Object to behavioral configuration.");
	unsigned int i;
	Trie<double>* behavioralConfig = new Trie<double>();
	Trie<JSONItem*>* trie = object->getTrie();
	DynamicArray<std::string>* keys = trie->getKeys();
	for(i = 0; i < keys->length(); i++)
	{
		behavioralConfig->add(*keys->get(i), ((JSONPrimitive<double>*)*trie->get(*keys->get(i)))->getPrimitive());
	}
	return behavioralConfig;
}

void RenderSim::parseCharacterConfig(Trie<JSONItem*>* trie)
{
	DEBUG_LOG("RENDERSIM", "Parsing character config.");
	tCharacterInfo* charInfo = new tCharacterInfo();
	Trie<IState*>* stateMap = new Trie<IState*>();
	stateMap->add("attack", new AttackState(NULL, NULL)); // these will be initialized in
	stateMap->add("patrol", new PatrolState(NULL, NULL)); // the character factory
	charInfo->type = ((JSONPrimitive<std::string>*)*trie->get("type"))->getPrimitive();
	charInfo->behavioralConfig = jsonObjectToBehavioralConfig((JSONObject*)*trie->get("config"));
	std::cout << "chance: " << *charInfo->behavioralConfig->get("chance") << std::endl;
	std::cout << "maxattack: " << *charInfo->behavioralConfig->get("maxattack") << std::endl;
	std::cout << "radius: " << *charInfo->behavioralConfig->get("radius") << std::endl;
	charInfo->stateMap = stateMap;
	charInfo->startState = ((JSONPrimitive<std::string>*)*trie->get("start"))->getPrimitive();
	charInfo->health = ((JSONPrimitive<unsigned int>*)*trie->get("health"))->getPrimitive();
	CharacterFactory::addCharacterInfo(charInfo->type, charInfo);
}
