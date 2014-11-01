#include "characterspawner.hh"

RandomLocationCharacterSpawner::RandomLocationCharacterSpawner(int maxSpawnTime, std::string type)
{
	timeChange = 0;
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
		std::srand(time(NULL));
		randomX = std::rand() % LevelManager::getInstance()->getWorldWidth();
		randomY = std::rand() % LevelManager::getInstance()->getWorldHeight();
		SceneManager::getInstance()->addSceneNode(CharacterFactory::get(type, randomX, randomY)->getSceneNode());
		spawnTime = std::rand() % maxSpawnTime + 1;
		timeChange = 0;
	}
}
