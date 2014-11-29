#include "character.hh"

Character::Character(int x, int y, unsigned int collisionLayer, unsigned int id, unsigned int health, unsigned int gold, double hydration, double energy, std::string type, Trie<double>* behavioralConfig, unsigned int teamNum) : IActor(collisionLayer, "CHARACTER", behavioralConfig)
{
	this->health = health;
	this->gold = gold;
	sceneNode = new SceneNode(x, y, *this, NULL, NULL);
	this->id = id;
	this->target = NULL;
	this->moveLocation = NULL;
	this->hydration = hydration;
	this->energy = energy;
	this->teamNum = teamNum;
	this->dead= false;
	this->level = 1;
	this->exp = 0;
	dispatcher = new Dispatcher();
	SceneManager::getInstance()->addTickable(dispatcher);
	setType(type);
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

unsigned int Character::getID()
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
		dead = true;
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

bool Character::sendKeyPress(int key, int cursorX, int cursorY)
{
	switch(key)
	{
		case 'm':
			setMoveLocation(cursorX, cursorY);
			dispatcher->dispatch(new StateEvent("moveto"));
			return true;
	}
	return false;
}

void Character::simulateNeeds()
{
	double dEnergy = *behavioralConfig->get("denergy");
	double dHydration = *behavioralConfig->get("dhydration");
	energy = energy - dEnergy > 0 ? energy - dEnergy : 0;
	hydration = hydration - dHydration > 0 ? hydration - dHydration : 0;
	DEBUG_LOG("CHARACTER", "Energy: " + std::to_string(energy) + ", Hydration: " + std::to_string(hydration) + ".");
}

void Character::sleep()
{
	double newEnergy = energy + *behavioralConfig->get("denergy") + *behavioralConfig->get("energyregen");
	energy = newEnergy < *behavioralConfig->get("maxenergy") ? newEnergy : *behavioralConfig->get("maxenergy");
}

bool Character::hasMaxEnergy()
{
	return energy == *behavioralConfig->get("maxenergy");
}

void Character::drink()
{
	double newHydration = hydration + *behavioralConfig->get("dhydration") + *behavioralConfig->get("hydrationregen");
	hydration = newHydration < *behavioralConfig->get("maxhydration") ? newHydration : *behavioralConfig->get("maxhydration");
}

bool Character::hasMaxHydration()
{
	return hydration == *behavioralConfig->get("maxhydration");
}

float Character::getProperty(std::string name)
{
	return *behavioralConfig->get(name);
}

float Character::getEnergy()
{
	return energy;
}

float Character::getHydration()
{
	return hydration;
}

bool Character::isDead()
{
	return dead;
}
