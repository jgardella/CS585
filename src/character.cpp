#include "character.hh"

Character::Character(int x, int y, unsigned int collisionLayer, unsigned int id, unsigned int health, unsigned int gold, unsigned int hydration, unsigned int energy, std::string type, Trie<double>* behavioralConfig, unsigned int teamNum) : IActor(collisionLayer, "CHARACTER", behavioralConfig)
{
	this->health = health;
	this->gold = gold;
	sceneNode = new SceneNode(x, y, *this, NULL, NULL);
	this->type = type;
	this->id = id;
	this->target = NULL;
	this->moveLocation = NULL;
	this->hydration = hydration;
	this->energy = energy;
	this->teamNum = teamNum;
	dispatcher = new Dispatcher();
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

void Character::takeDamage(Character* attacker, unsigned int damage)
{
	DEBUG_LOG("CHARACTER", "Character #" + std::to_string(id) + " taking " + std::to_string(damage) + " damage.");
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
		dispatcher->dispatch(new DeathEvent(attacker, this));
	}
}

std::string Character::inspect()
{
	std::string str = "Health: " + std::to_string(health) + " | Type: " + type + " | ID: " + std::to_string(id) + " | Gold: " + std::to_string(gold) + " | Hydration: " + std::to_string(hydration) + " | Energy: " + std::to_string(energy);
	if(target != NULL)
	{
		str.append(" | Target: " + target->getType() + " #" + std::to_string(target->getID()));
	}
	else
	{
		str.append(" | Target: NO TARGET");
	}
	return str;
}

void Character::setTarget(Character* target)
{
	this->target = target;
}

Character* Character::getTarget()
{
	return target;
}

void Character::setGold(unsigned int newValue)
{
	gold = newValue;
}

unsigned int Character::getGold()
{
	return gold;
}

unsigned int Character::getTeam()
{
	return teamNum;
}

void Character::setMoveLocation(int x, int y)
{
	if(moveLocation != NULL)
	{
		delete moveLocation;
	}
	moveLocation = new tPosition(x, y);
}

tPosition* Character::getMoveLocation()
{
	return moveLocation;
}

void Character::nullifyMoveLocation()
{
	moveLocation = NULL;
}

void Character::addListener(std::string eventType, IListenerCallback* callback)
{
	dispatcher->addListener(eventType, callback);
}
