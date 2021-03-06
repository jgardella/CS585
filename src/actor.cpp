#include "actor.hh"
#include "debug.hh"

Actor::Actor(std::string name, int initialX, int initialY, unsigned int col, Trie<double>* behavioralConfig) : IActor(col, "ACTOR", behavioralConfig)
{
	DEBUG_LOG("ACTOR", "Creating Actor with (name: " + name + ", initialX: " + std::to_string(initialX) + ", initialY: " + std::to_string(initialY) + ", col: " + std::to_string(col) + ").");
	this->name = name;
	sceneNode = new SceneNode(initialX, initialY, *this, NULL, NULL);
	DEBUG_LOG("ACTOR", "Scene node added to graph.");
	SceneManager::getInstance()->addSceneNode(sceneNode);
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

void Actor::remove()
{
	SceneManager::getInstance()->removeSceneNode(sceneNode);
	removed = true;
}

bool Actor::isRemoved()
{
	return removed;
}

SceneNode* Actor::getSceneNode()
{
	return sceneNode;
}

std::string Actor::inspect()
{
	return "Name: " + name + "\n";
}

bool Actor::sendKeyPress(int key, int cursorX, int cursorY)
{
	return true;
}
