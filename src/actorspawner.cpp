#include "actorspawner.hh"
#include <string>
#include <ctime>

ActorSpawner::ActorSpawner(int secondsBetweenSpawns, DynamicArray<Actor*> *actors, int spawnX, int spawnY)
{
	DEBUG_LOG("SPAWNER", "Constructing ActorSpawner with (secondsBetweenSpawns: " + std::to_string(secondsBetweenSpawns) + ", spawnX: " + std::to_string(spawnX) + ", spawnY: " + std::to_string(spawnY) + ".");
	this->actors = actors;
	names = new DynamicArray<std::string*>();
	names->pushBack(new std::string("Jason"));
	names->pushBack(new std::string("Pat"));
	names->pushBack(new std::string("Nick"));
	names->pushBack(new std::string("Pete"));
	names->pushBack(new std::string("Steve"));
	names->pushBack(new std::string("Jeff"));
	names->pushBack(new std::string("John"));
	names->pushBack(new std::string("Aaron"));
	names->pushBack(new std::string("Chris"));
	names->pushBack(new std::string("Bill"));
	names->pushBack(new std::string("Ben"));
	names->pushBack(new std::string("Joe"));
	names->pushBack(new std::string("Jack"));
	names->pushBack(new std::string("Alex"));
	names->pushBack(new std::string("Dan"));
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
		std::srand(time(NULL));
		DEBUG_LOG("SPAWNER", "Actor spawner spawning new actor.");
		Actor *newActor = new Actor(*names->remove(rand() % names->length()), spawnX, spawnY, true, NULL);
		DEBUG_LOG("GAMEPLAY", "Spawning " + newActor->getName() + " at (" + std::to_string(spawnX) + ", " + std::to_string(spawnY) + ").");
		actors->pushBack(newActor);
		DEBUG_LOG("SPAWNER", "Actor added to actors array.");
		timeCounter = 0;
	}
}
