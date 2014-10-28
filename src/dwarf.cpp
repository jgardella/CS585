#include "dwarf.hh"

Dwarf::Dwarf(int x, int y, unsigned int collisionLayer, unsigned int health) : IActor(collisionLayer, "DWARF")
{
	this->health = health;
	sceneNode = new SceneNode(x, y, *this, NULL, NULL);
}

Dwarf::~Dwarf()
{

}

void Dwarf::setX(int x)
{
	sceneNode->setX(x);
}

void Dwarf::setY(int y)
{
	sceneNode->setY(y);
}

int Dwarf::getX()
{
	return sceneNode->getX();
}

int Dwarf::getY()
{
	return sceneNode->getY();
}

SceneNode* Dwarf::getSceneNode()
{
	return sceneNode;
}
