#ifndef _ACTORSPAWNER_HH_
#define _ACTORSPAWNER_HH_

#include "actor.hh"
#include "itickable.hh"
#include "scenemanager.hh"
#include "dynamicarray.hh"
#include <cstdlib>
#include "debug.hh"

class ActorSpawner : public ITickable
{
	public:
		ActorSpawner(int, DynamicArray<Actor*>*, int, int);
		void tick(float dt);
	private:
		SceneManager *sceneManager;
		DynamicArray<std::string> *names;
		DynamicArray<Actor*> *actors;
		int secondsBetweenSpawns;
		int namesLeft;
		int spawnX;
		int spawnY;
		float timeCounter;
		Debug *debug;
};

#endif
