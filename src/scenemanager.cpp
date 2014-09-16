#include "scenemanager.hh"
#include "fixedgrid.hh"
#include <iostream>

SceneManager* SceneManager::instance;

SceneManager* SceneManager::getInstance()
{
	if(SceneManager::instance == NULL)
	{
		SceneManager::instance = new SceneManager();
	}
	return SceneManager::instance;
}

SceneManager::SceneManager()
{	
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
	tickable->setGraph(sceneGraph);
	tickables->pushBack(tickable);
}

void SceneManager::addSceneNode(SceneNode node)
{
	sceneNodes->pushBack(node);
}
