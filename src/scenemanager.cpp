#include "scenemanager.hh"

template SceneManager* SceneManager::getInstance();
template <class SpacialStructure>
SceneManager* SceneManager::getInstance()
{
	if(instance == NULL)
	{
		instance = new SceneManager();
	}
	return instance;
}

template SceneManager::SceneManager();
template <class SpacialStructure>
SceneManager::SceneManager(): 
	tickables(new DynamicArray<ITickable>()),
	sceneNodes(new DynamicArray<SceneNode>())
	sceneGraph(new SpacialStructure())
{}

template <class SpacialStructure>
void SceneManager::tick(float dt)
{
	int i;
	for(i = 0; i < tickables.length(); i++)
	{
		tickables.get(i).tick(dt);
	}
}

template <class SpacialStructure>
void SceneManager::addTickable(ITickable tickable)
{
	tickables.push(tickable);
}

template <class SpacialStructure>
void SceneManager::addSceneNode(SceneNode node)
{
	sceneNodes.push(node);
}
