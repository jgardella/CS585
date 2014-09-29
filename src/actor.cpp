#include "actor.hh"
#include "debug.hh"

Actor::Actor(std::string name, int initialX, int initialY, bool col) : IActor(col, "ACTOR")
{
	Debug::getInstance()->log("ACTOR", "Creating Actor.");
	this->name = name;
	sceneNode = new SceneNode(initialX, initialY, NULL, NULL);
	Debug::getInstance()->log("ACTOR", "Scene node added to graph.");
	SceneManager::getInstance()->addSceneNode(*sceneNode);
	readyForRemoval = false;
}

Actor::~Actor()
{

}

std::string Actor::getName()
{
	return name;
}

SceneNode* Actor::getSceneNode()
{
	return sceneNode;
}

void Actor::markForRemoval()
{
	readyForRemoval = true;
}

bool Actor::isMarkedForRemoval()
{
	return readyForRemoval;
}
