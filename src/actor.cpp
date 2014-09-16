#include "actor.hh"
#include "debug.hh"
#include <iostream>

Actor::~Actor()
{
//	delete sceneNode;
}

Actor::Actor(std::string name, int initialX, int initialY, bool col)
{
	Debug::log("ACTOR", "Creating Actor.");
	this->name = name;
	sceneNode = new SceneNode(initialX, initialY, col, NULL, NULL);
	Debug::log("ACTOR", "Scene node added to graph.");
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
