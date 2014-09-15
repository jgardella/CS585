#ifndef _GAMEOBJECT_HH_
#define _GAMEOBJECT_HH_

#include "scenemanager.hh"
#include "dynamicarray.hh"
#include "actor.hh"
#include "actorspawner.hh"

class GameObject
{
	public:
		GameObject();
		bool update(float dt);
	private:
		SceneManager *sceneManager;
		DynamicArray<Actor*> *actors;
		float timeSinceStart;
};

#endif
