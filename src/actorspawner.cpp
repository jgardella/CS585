#include "actorspawner.hh"
#include <string>

ActorSpawner::ActorSpawner(int secondsBetweenSpawns, DynamicArray<Actor*> *actors, int spawnX, int spawnY)
{
	DEBUG_LOG("SPAWNER", "Constructing ActorSpawner.");
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

ActorSpawner::~ActorSpawner()
{
	delete names;
}

void ActorSpawner::tick(float dt)
{
	timeCounter += dt;
	if(timeCounter >= secondsBetweenSpawns)
	{
		DEBUG_LOG("SPAWNER", "Actor spawner spawning new actor.");
		Actor *newActor = new Actor(*names->get(randomName++), spawnX, spawnY, true);
		DEBUG_LOG("GAMEPLAY", "Spawning " + newActor->getName() + " at (" + std::to_string(spawnX) + ", " + std::to_string(spawnY) + ").");
		actors->pushBack(newActor);
		DEBUG_LOG("SPAWNER", "Actor added to actors array.");
		timeCounter = 0;
	}
}
