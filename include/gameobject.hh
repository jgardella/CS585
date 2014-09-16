#ifndef _GAMEOBJECT_HH_
#define _GAMEOBJECT_HH_

#include "scenemanager.hh"
#include "dynamicarray.hh"
#include "actor.hh"
#include "actorspawner.hh"

// Game object class
class GameObject
{
	public:
		// Constructs default game object.
		GameObject();
		// Calls tick on scene manager.
		bool update(float dt);
	private:
		SceneManager *sceneManager;
		DynamicArray<Actor*> *actors;
		float timeSinceStart;
};

#endif
