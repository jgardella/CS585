#include "character.hh"

Character::Character(int x, int y, unsigned int collisionLayer, unsigned int id, unsigned int health, std::string type) : IActor(collisionLayer, "CHARACTER")
{
	this->health = health;
	sceneNode = new SceneNode(x, y, *this, NULL, NULL);
	this->type = type;
	this->id = id;
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

int Character::getID()
{
	return id;
}

int Character::getHealth()
{
	return health;
}

SceneNode* Character::getSceneNode()
{
	return sceneNode;
}

std::string Character::getType()
{
	return type;
}

void Character::takeDamage(unsigned int damage)
{
	if(damage >= health)
	{
		health = 0;
	}
	else
	{
		health -= damage;
	}
	if(health == 0)
	{
		SceneManager::getInstance()->removeSceneNode(sceneNode);
	}
}

std::string Character::inspect()
{
	return "Health: " + std::to_string(health) + " | Type: " + type + " | ID: " + std::to_string(id);
}
