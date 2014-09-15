#include "gameobject.hh"
#include "debug.hh"
#include "randomwalkcontroller.hh"

GameObject::GameObject()
{
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
		return false;
	}

	sceneManager->tick(dt);
	for(i = 0; i < actors->length(); i++)
	{
		if(actors->get(i)->getSceneNode() == NULL)
		{
			delete actors->remove(i--);
		}
	}
	return true;
}
