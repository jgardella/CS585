#include "scenemanager.hh"

SceneManager* SceneManager::getInstance()
{
	if(instance == NULL)
	{
		instance = new SceneManager();
	}
	return instance;
}

SceneManager::SceneManager(): 
	tickables(new DynamicArray<ITickable>()),
	sceneNodes(new DynamicArray<SceneNode>())
	sceneGraph(new SpacialStructure())
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
