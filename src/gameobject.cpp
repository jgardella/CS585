#include "gameobject.hh"
#include "debug.hh"
#include "randomwalkcontroller.hh"

GameObject::GameObject()
{
	Debug::log("GAMEOBJ", "Constructing game object.");
	sceneManager = SceneManager::getInstance();
	actors = new DynamicArray<Actor*>();
	sceneManager->addTickable(new ActorSpawner(2, actors, 4, 4));
	sceneManager->addTickable(new RandomWalkController(actors));
	timeSinceStart = 0;
}

bool GameObject::update(float dt)
{
	unsigned int i;
	timeSinceStart += dt;
	if(timeSinceStart >= 30)
	{
		Debug::log(Debug::GAMEPLAY, "Simulation finished. Remaining actors:");
		for(i = 0; i < actors->length(); i++)
		{
			Debug::log(Debug::GAMEPLAY, actors->get(i)->getName());
		}
		return false;
	}
	sceneManager->tick(dt);
	return true;
}
