#include "orc.hh"

Orc::Orc(int x, int y, unsigned int collisionLayer, unsigned int health) : IActor(collisionLayer, "ORC")
{
	this->health = health;
	sceneNode = new SceneNode(x, y, *this, NULL, NULL);
}

Orc::~Orc()
{

}

void Orc::setX(int x)
{
	sceneNode->setX(x);
}

void Orc::setY(int y)
{
	sceneNode->setY(y);
}

int Orc::getX()
{
	return sceneNode->getX();
}

int Orc::getY()
{
	return sceneNode->getY();
}

SceneNode* Orc::getSceneNode()
{
	return sceneNode;
}
