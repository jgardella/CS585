#include "character.hh"

Character::Character(int x, int y, unsigned int collisionLayer, unsigned int health, std::string type) : IActor(collisionLayer, "CHARACTER")
{
	this->health = health;
	sceneNode = new SceneNode(x, y, *this, NULL, NULL);
	this->type = type;
}

Character::~Character()
{

}

void Character::setX(int x)
{
	sceneNode->setX(x);
}

void Character::setY(int y)
{
	sceneNode->setY(y);
}

int Character::getX()
{
	return sceneNode->getX();
}

int Character::getY()
{
	return sceneNode->getY();
}

SceneNode* Character::getSceneNode()
{
	return sceneNode;
}

std::string Character::getType()
{
	return type;
}
