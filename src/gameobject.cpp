#include "gameobject.hh"
#include "debug.hh"

GameObject::GameObject()
{
	sceneManager = SceneManager::getInstance();
	actors = new DynamicArray<Actor*>();
	sceneManager->addTickable(new ActorSpawner(2, actors, 4, 4));
	timeSinceStart = 0;
}

bool GameObject::update(float dt)
{
	timeSinceStart += dt;
	if(dt >= 30)
	{
		return false;
	}
	sceneManager->tick(dt);
	return true;
}
