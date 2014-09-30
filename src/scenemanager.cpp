#include "scenemanager.hh"
#include "fixedgrid.hh"
#include "debug.hh"

SceneManager* SceneManager::instance;

SceneManager* SceneManager::getInstance()
{
	Debug::getInstance()->log("MANAGER", "Getting instance of scene manager.");
	if(SceneManager::instance == NULL)
	{
		SceneManager::instance = new SceneManager();
	}
	return SceneManager::instance;
}

SceneManager::SceneManager()
{	
	Debug::getInstance()->log("MANAGER", "Constructing scene manager.");
	tickables = new DynamicArray<ITickable*>();
	sceneNodes = new DynamicArray<SceneNode>();
	sceneGraph = new FixedGrid();
}

void SceneManager::tick(float dt)
{
	unsigned int i;
	for(i = 0; i < tickables->length(); i++)
	{
		(*tickables->get(i))->tick(dt);
	}
}

void SceneManager::addTickable(ITickable *tickable)
{
	Debug::getInstance()->log("MANAGER", "Adding tickable to scene manager.");
	tickables->pushBack(tickable);
}

void SceneManager::addSceneNode(SceneNode node)
{
	Debug::getInstance()->log("MANAGER", "Adding scenenode to scene manager.");
	sceneNodes->pushBack(node);
}
