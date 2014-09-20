#include "actorspawner.hh"

ActorSpawner::ActorSpawner(int secondsBetweenSpawns, DynamicArray<Actor*> *actors, int spawnX, int spawnY)
{
	Debug::getInstance()->log("SPAWNER", "Constructing ActorSpawner.");
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
	randomName = 0;
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
		Debug::getInstance()->log("SPAWNER", "Actor spawner spawning new actor.");
		Actor *newActor = new Actor(names->get(randomName++), spawnX, spawnY, true);
		Debug::getInstance()->log("GAMEPLAY", "Spawning " + newActor->getName());
		actors->pushBack(newActor);
		Debug::getInstance()->log("SPAWNER", "Actor added to actors array.");
		timeCounter = 0;
	}

}

void ActorSpawner::setGraph(ISceneGraph *graph)
{
	this->graph = graph;
}
