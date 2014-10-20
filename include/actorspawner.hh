#ifndef _ACTORSPAWNER_HH_
#define _ACTORSPAWNER_HH_

#include "actor.hh"
#include "itickable.hh"
#include "scenemanager.hh"
#include "dynamicarray.hh"
#include <cstdlib>
#include "debug.hh"

// Tickable which spawns actors.
class ActorSpawner : public ITickable
{
	public:
		// Constructs a spawner.
		ActorSpawner(int, DynamicArray<Actor*>*, int, int);
		
		// Destructs the actor spawner.
		~ActorSpawner();

		// Ticks the spawner.
		void tick(float dt);
	private:
		DynamicArray<std::string*> *names;
		DynamicArray<Actor*> *actors;
		int secondsBetweenSpawns;
		int spawnX;
		int spawnY;
		float timeCounter;
		Debug *debug;
};

#endif
