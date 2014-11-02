#include "randomlocationcharacterspawner.hh"

RandomLocationCharacterSpawner::RandomLocationCharacterSpawner(int maxSpawnTime, std::string type)
{
	DEBUG_LOG("RANDLOCCHARSPAWN", "Constructing spawner with (maxSpawnTime: " + std::to_string(maxSpawnTime) + ", type: " + type + ").");
	timeChange = 0;
	this->type = type;
	this->maxSpawnTime = maxSpawnTime;
	std::srand(time(NULL));
	spawnTime = std::rand() % maxSpawnTime + 1;
}

void RandomLocationCharacterSpawner::tick(float dt)
{
	int randomX;
	int randomY;
	timeChange += dt;
	if(timeChange >= spawnTime)
	{
		randomX = std::rand() % LevelManager::getInstance()->getWorldWidth();
		randomY = std::rand() % LevelManager::getInstance()->getWorldHeight();
		DEBUG_LOG("RANDLOCCHARSPAWN", "Spawning " + type + " at (" + std::to_string(randomX) + ", " + std::to_string(randomY) + ").");
		SceneManager::getInstance()->addSceneNode(CharacterFactory::get(type, randomX, randomY)->getSceneNode());
		spawnTime = std::rand() % maxSpawnTime + 1;
		DEBUG_LOG("RANDLOCCHARSPAWN", "Spawn time set to " + std::to_string(spawnTime) + ".");
		timeChange = 0;
	}
}
