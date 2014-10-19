// Wrapper functions for SceneManager's SceneGraph.
#include "scenemanager.hh"

void SceneManager::addSceneNode(SceneNode* node)
{
	DEBUG_LOG("MANAGER", "Adding scenenode to scene manager.");
	sceneGraph->addSceneNode(node);
}

void SceneManager::removeSceneNode(SceneNode* node)
{
	sceneGraph->removeSceneNode(node);
}

void SceneManager::updateSceneNode(SceneNode* node, int x, int y)
{
	DEBUG_LOG("MANAGER", "Updating scene node to position (" + std::to_string(x) + ", " + std::to_string(y) + ").");
	sceneGraph->updateSceneNode(node, x, y);
}

DynamicArray<SceneNode*>* SceneManager::getColliders(SceneNode* node)
{
	return sceneGraph->getColliders(node);
}

DynamicArray<SceneNode*>* SceneManager::getColliders(int x, int y)
{
	DEBUG_LOG("MANAGER", "Getting colliders at position (" + std::to_string(x) + ", " + std::to_string(y) + ").");
	return sceneGraph->getColliders(x, y);
}

DynamicArray<SceneNode*>* SceneManager::getColliders(int x, int y, int radius)
{
	DEBUG_LOG("MANAGER", "Getting colliders within circle of center (" + std::to_string(x) + ", " + std::to_string(y) + ") and of radius " + std::to_string(radius) + ".");
	return sceneGraph->getColliders(x, y, radius);
}

DynamicArray<SceneNode*>* SceneManager::getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2)
{
	DEBUG_LOG("MANAGER", "Getting colliders within rectangle of corners (" + std::to_string(cornerX1) + ", " + std::to_string(cornerY1) + ") and (" + std::to_string(cornerX2) + ", " + std::to_string(cornerY2) + ".");
	return sceneGraph->getColliders(cornerX1, cornerY1, cornerX2, cornerY2);
}
