#include "attackstate.hh"

AttackState::AttackState(Character* character) : IState(character)
{
	this->character = character;
}

void AttackState::tick(float dt)
{
	if(character->getTarget() == NULL) // scan for ((Character*)actor)->getTarget()
	{
		scanForTarget();
	}
	if(character->getTarget() == NULL) // ((Character*)actor)->getTarget() not found, return to patrol
	{
		DEBUG_LOG("ATTACKSTATE", "Target not found, transitioning to patrol state.");
		dispatcher->dispatch(new StateEvent("patrol"));
	}
	else
	{
		if(targetInRange())
		{
			attackTarget();
		}
		else
		{
			moveTowardTarget();
		}
	}
	dispatcher->tick(dt);
}

void AttackState::scanForTarget()
{
	DEBUG_LOG("ATTACKSTATE", "Scanning for target.");
	unsigned int i;
	Character* otherCharacter;
	int radius = (int) *actor->getBehavioralConfig()->get("radius") + 2;
	DEBUG_LOG("ATTACKSTATE", "Radius: " + std::to_string(radius));
	DynamicArray<SceneNode*>* nodes = SceneManager::getInstance()->getColliders(((Character*)actor)->getX(), ((Character*)actor)->getY(), radius); 
	for(i = 0; i < nodes->length(); i++)
	{
		if((*nodes->get(i))->getActor()->getClass().compare("CHARACTER") == 0)
		{
			otherCharacter = (Character*)(*nodes->get(i))->getActor();
			if(character->getTeam() != (otherCharacter->getTeam()) && !character->isDead())
			{
				DEBUG_LOG("ATTACKSTATE", "Found target."); 
				character->setTarget(otherCharacter);
				return;
			}
		}
	}
}

void AttackState::moveTowardTarget()
{
	DEBUG_LOG("ATTACKSTATE", "Moving toward target."); 
	int xDist = character->getX() - character->getTarget()->getX();
	int yDist = character->getY() - character->getTarget()->getY();
	int newX = character->getX();
	int newY = character->getY();
	if(yDist < 0)
	{
		newY += 1;
	}
	else if(yDist > 0)
	{
		newY -= 1;
	}
	if(xDist < 0)
	{
		newX += 1;
	}
	else if(xDist > 0)
	{
		newX -= 1;
	}
	DEBUG_LOG("ATTACKSTATE", "Moving to (" + std::to_string(newX) + ", " + std::to_string(newY) + ").");
	SceneManager::getInstance()->updateSceneNode(character->getSceneNode(), newX, newY);
}

bool AttackState::targetInRange()
{
	bool inRange = std::abs(character->getX() - character->getTarget()->getX()) <= 1 && std::abs(character->getY() - character->getTarget()->getY()) <= 1;
	DEBUG_LOG("ATTACKSTATE", "Character #" + std::to_string(character->getTarget()->getID()) + " is in range of Character #" + std::to_string(character->getID()) + ": " + std::to_string(inRange) + ".");
	return inRange;
}

void AttackState::attackTarget()
{
	DEBUG_LOG("ATTACKSTATE", "Attempting to attack ((Character*)actor)->getTarget().");
	int rand = std::rand() % 100 + 1;
	int hitChance = character->getWeapon()->getHitChance() + (character->getLevel() - character->getTarget()->getLevel()) * 10 - character->getTarget()->getArmor()->getBlockChance();
	if(rand <= hitChance)
	{
		character->getTarget()->takeDamage(character, character->getWeapon()->getDamage() - character->getArmor()->getDefence());
	}
}

unsigned int AttackState::getAttackDamage()
{
	return std::rand() % (unsigned int)*actor->getBehavioralConfig()->get("maxattack") + 1;
}
