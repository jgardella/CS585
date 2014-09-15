#include "actor.hh"

Actor::Actor(std::string name, int initialX, int initialY, int collisionLayer)
{
	this->name = name;
	sceneNode = new SceneNode(initialX, initialY, collisionLayer, NULL, NULL);
}

std::string Actor::getName()
{
	return name;
}

SceneNode* Actor::getSceneNode()
{
	return sceneNode;
}
