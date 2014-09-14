#include "scenemanager.hh"
#include <time.h>

SceneManager::SceneManager(): 
	tickables(new DynamicArray<ITickable>()),
	sceneNodes(new DynamicArray<SceneNode>())
{}

void SceneManager::tick(float dt)
{
	int i;
	for(i = 0; i < tickables.length(); i++)
	{
		tickables.get(i).tick(dt);
	}
}

void SceneManager::addTickable(ITickable tickable)
{
	tickables.push(tickable);
}

void SceneManager::addSceneNode(SceneNode node)
{
	sceneNodes.push(node);
}
