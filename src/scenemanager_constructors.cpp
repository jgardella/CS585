// Constructors and construction related methods for SceneManager.
#include "scenemanager.hh"

SceneManager* SceneManager::instance;

SceneManager::SceneManager()
{	
	DEBUG_LOG("MANAGER", "Constructing scene manager.");
	this->tickables = new DynamicArray<ITickable*>();
}

SceneManager* SceneManager::getInstance()
{
	if(instance == NULL)
	{
		instance = new SceneManager();
	}
	return instance;
}

void SceneManager::setGraph(ISceneGraph* graph)
{
	sceneGraph = graph;
}
