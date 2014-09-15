#include "actor.hh"

Actor::Actor(std::string name, int initialX, int initialY, Collider col)
{
	this->name = name;
	sceneNode = new SceneNode(initalX, intialY, col, NULL, NULL);
}

std::string Actor::getName()
{
	return name;
}
