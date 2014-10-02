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
}

void SceneManager::setGraph(ISceneGraph* graph)
{
	sceneGraph = graph;
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

// Wrapper function for scene graph

void SceneManager::addSceneNode(SceneNode* node)
{
	Debug::getInstance()->log("MANAGER", "Adding scenenode to scene manager.");
	sceneGraph->addSceneNode(node);
}

void SceneManager::removeSceneNode(SceneNode* node)
{
	sceneGraph->removeSceneNode(node);
}

void SceneManager::updateSceneNode(SceneNode* node, int x, int y)
{
	sceneGraph->updateSceneNode(node, x, y);
}

DynamicArray<SceneNode*>* SceneManager::getColliders(SceneNode* node)
{
	return sceneGraph->getColliders(node);
}

DynamicArray<SceneNode*>* SceneManager::getColliders(int x, int y)
{
	return sceneGraph->getColliders(x, y);
}

DynamicArray<SceneNode*>* SceneManager::getColliders(int x, int y, int radius)
{
	return sceneGraph->getColliders(x, y, radius);
}

DynamicArray<SceneNode*>* SceneManager::getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2)
{
	return sceneGraph->getColliders(cornerX1, cornerY1, cornerX2, cornerY2);
}
