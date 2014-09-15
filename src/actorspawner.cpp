#include "actorspawner.hh"

ActorSpawner::ActorSpawner(int secondsBetweenSpawns, DynamicArray<Actor*> *actors, int spawnX, int spawnY)
{
	sceneManager = SceneManager::getInstance();
	this->actors = actors;
	names = new DynamicArray<std::string>();
	names->pushBack("Jason");
	names->pushBack("Pat");
	names->pushBack("Nick");
	names->pushBack("Pete");
	names->pushBack("Steve");
	names->pushBack("Jeff");
	names->pushBack("John");
	names->pushBack("Aaron");
	names->pushBack("Chris");
	names->pushBack("Bill");
	names->pushBack("Ben");
	names->pushBack("Joe");
	names->pushBack("Jack");
	names->pushBack("Alex");
	names->pushBack("Dan");
	namesLeft = 15;
	this->spawnX = spawnX;
	this->spawnY = spawnY;
	this->secondsBetweenSpawns = secondsBetweenSpawns;
	this->timeCounter = 0;
}

void ActorSpawner::tick(float dt)
{
	timeCounter += dt;
	if(timeCounter >= secondsBetweenSpawns)
	{
		Actor *newActor = new Actor(names->get(rand() % namesLeft--), spawnX, spawnY, true);
		Debug::log(Debug::GAMEPLAY, "Spawning " + newActor->getName());
		actors->pushBack(newActor);
		timeCounter = 0;
	}

}
