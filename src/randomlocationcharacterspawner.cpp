#include "randomlocationcharacterspawner.hh"

RandomLocationCharacterSpawner::RandomLocationCharacterSpawner(int minSpawnTime, int maxSpawnTime, std::string type)
{
	DEBUG_LOG("RANDLOCCHARSPAWN", "Constructing spawner with (maxSpawnTime: " + std::to_string(maxSpawnTime) + ", type: " + type + ").");
	timeChange = 0;
	this->type = type;
	this->maxSpawnTime = maxSpawnTime;
	this->minSpawnTime = minSpawnTime;
	spawnTime = std::rand() % maxSpawnTime + 1;
}

void RandomLocationCharacterSpawner::tick(float dt)
{
	int randomX;
	int randomY;
	timeChange += dt;
	if(timeChange >= spawnTime)
	{
		do
		{
			randomX = std::rand() % LevelManager::getInstance()->getWorldWidth();
			randomY = std::rand() % LevelManager::getInstance()->getWorldHeight();
		}
		while(SceneManager::getInstance()->getColliders(randomX, randomY, true)->length() != 0); // randomize position until it is unoccupied
		DEBUG_LOG("RANDLOCCHARSPAWN", "Spawning " + type + " at (" + std::to_string(randomX) + ", " + std::to_string(randomY) + ").");
		CharacterFactory::get(type, randomX, randomY)->getSceneNode();
		spawnTime = std::rand() % maxSpawnTime + 1;
		DEBUG_LOG("RANDLOCCHARSPAWN", "Spawn time set to " + std::to_string(spawnTime) + ".");
		timeChange = 0;
	}
}
