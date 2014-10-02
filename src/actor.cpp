#include "actor.hh"
#include "debug.hh"

Actor::Actor(std::string name, int initialX, int initialY, bool col) : IActor(col, "ACTOR")
{
	Debug::getInstance()->log("ACTOR", "Creating Actor.");
	this->name = name;
	sceneNode = new SceneNode(initialX, initialY, *this, NULL, NULL);
	Debug::getInstance()->log("ACTOR", "Scene node added to graph.");
	SceneManager::getInstance()->addSceneNode(*sceneNode);
	readyForRemoval = false;
}

Actor::~Actor()
{
	delete sceneNode;
}

std::string Actor::getName()
{
	return name;
}

void Actor::setX(int x)
{
	sceneNode->setX(x);
}

void Actor::setY(int y)
{
	sceneNode->setY(y);
}

int Actor::getX()
{
	return sceneNode->getX();
}

int Actor::getY()
{
	return sceneNode->getY();
}

void Actor::markForRemoval()
{
	readyForRemoval = true;
}

bool Actor::isMarkedForRemoval()
{
	return readyForRemoval;
}
