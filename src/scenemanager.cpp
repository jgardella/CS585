#include "scenemanager.hh"
#include "fixedgrid.hh"
#include "debug.hh"

SceneManager* SceneManager::instance;

SceneManager* SceneManager::getInstance()
{
	Debug::log("MANAGER", "Getting instance of scene manager.");
	if(SceneManager::instance == NULL)
	{
		SceneManager::instance = new SceneManager();
	}
	return SceneManager::instance;
}

SceneManager::SceneManager()
{	
	Debug::log("MANAGER", "Constructing scene manager.");
	tickables = new DynamicArray<ITickable*>();
	sceneNodes = new DynamicArray<SceneNode>();
	sceneGraph = new FixedGrid();
}

void SceneManager::tick(float dt)
{
	unsigned int i;
	for(i = 0; i < tickables->length(); i++)
	{
		tickables->get(i)->tick(dt);
	}
}

void SceneManager::addTickable(ITickable *tickable)
{
	Debug::log("MANAGER", "Adding tickable to scene manager.");
	tickable->setGraph(sceneGraph);
	tickables->pushBack(tickable);
}

void SceneManager::addSceneNode(SceneNode node)
{
	Debug::log("MANAGER", "Adding scenenode to scene manager.");
	sceneNodes->pushBack(node);
}
