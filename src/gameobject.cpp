#include "gameobject.hh"

GameObject::GameObject()
{
	sceneManager = SceneManager::getInstance();
	actors = new DynamicArray<Actor>();
}

bool update(float dt)
{
	sceneManager->tick(dt);
}
