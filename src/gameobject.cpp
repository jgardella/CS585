#include "gameobject.hh"
#include "debug.hh"
#include "fixedgrid.hh"
#include "randomwalkcontroller.hh"


GameObject::GameObject()
{
	DEBUG_LOG("GAMEOBJ", "Constructing game object.");
	actors = new DynamicArray<Actor*>();
	SceneManager::getInstance()->setGraph(new FixedGrid());
	SceneManager::getInstance()->addTickable(new RandomWalkController(actors));
	SceneManager::getInstance()->addTickable(new ActorSpawner(2, actors, 4, 4));
	timeSinceStart = 0;
}

bool GameObject::update(float dt)
{
	unsigned int i;
	timeSinceStart += dt;
	if(timeSinceStart >= 30)
	{
		DEBUG_LOG("GAMEPLAY", "Simulation finished. Remaining actors:");
		for(i = 0; i < actors->length(); i++)
		{
			if(!(*actors->get(i))->isRemoved())
			{	
				DEBUG_LOG("GAMEPLAY", (*actors->get(i))->getName());
			}
		}
		return false;
	}
	SceneManager::getInstance()->tick(dt);
	return true;
}
