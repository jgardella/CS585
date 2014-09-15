#include "actor.hh"
#include <iostream>

Actor::Actor(std::string name, int initialX, int initialY, bool col)
{
	std::cout << "creating actor" << std::endl;
	this->name = name;
	sceneNode = new SceneNode(initialX, initialY, col, NULL, NULL);
	SceneManager::getInstance()->addSceneNode(*sceneNode);
}

std::string Actor::getName()
{
	return name;
}

SceneNode* Actor::getSceneNode()
{
	return sceneNode;
}
