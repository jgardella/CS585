#include "attackstate.hh"

void AttackState::tick(float dt)
{
	if(((Character*)actor)->getTarget() == NULL) // scan for ((Character*)actor)->getTarget()
	{
		scanForTarget();
	}
	if(((Character*)actor)->getTarget() == NULL) // ((Character*)actor)->getTarget() not found, return to patrol
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
	Character* character;
	int radius = (int) *actor->getBehavioralConfig()->get("radius");
	DEBUG_LOG("ATTACKSTATE", "Radius: " + std::to_string(radius));
	DynamicArray<SceneNode*>* nodes = SceneManager::getInstance()->getColliders(((Character*)actor)->getX(), ((Character*)actor)->getY(), radius); 
	for(i = 0; i < nodes->length(); i++)
	{
		character = (Character*)(*nodes->get(i))->getActor();
		if(((Character*)actor)->getTeam() != (character->getTeam()))
		{
			DEBUG_LOG("ATTACKSTATE", "Found target."); 
			((Character*)actor)->setTarget(character);
			return;
		}
	}
}

void AttackState::moveTowardTarget()
{
	DEBUG_LOG("ATTACKSTATE", "Moving toward target."); 
	int xDist = ((Character*)actor)->getX() - ((Character*)actor)->getTarget()->getX();
	int yDist = ((Character*)actor)->getY() - ((Character*)actor)->getTarget()->getY();
	int newX = ((Character*)actor)->getX();
	int newY = ((Character*)actor)->getY();
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
	SceneManager::getInstance()->updateSceneNode(((Character*)actor)->getSceneNode(), newX, newY);
}

bool AttackState::targetInRange()
{
	bool inRange = std::abs(((Character*)actor)->getX() - ((Character*)actor)->getTarget()->getX()) <= 1 && std::abs(((Character*)actor)->getY() - ((Character*)actor)->getTarget()->getY()) <= 1;
	DEBUG_LOG("ATTACKSTATE", "Character #" + std::to_string(((Character*)actor)->getTarget()->getID()) + " is in range of Character #" + std::to_string(((Character*)actor)->getID()) + ": " + std::to_string(inRange) + ".");
	return inRange;
}

void AttackState::attackTarget()
{
	DEBUG_LOG("ATTACKSTATE", "Attempting to attack ((Character*)actor)->getTarget().");
	/*int damage; // reimplement later
	float rand = std::rand() / ((float) RAND_MAX);
	if(rand < *actor->getBehavioralConfig()->get("chance"))
	{
		damage = getAttackDamage();
		DEBUG_LOG("ATTACKSTATE", "Attacking ((Character*)actor)->getTarget() with damage " + std::to_string(damage) + ".");
		DEBUG_LOG("GAMEPLAY", "Attacking ((Character*)actor)->getTarget() with damage " + std::to_string(damage) + ".");	
		((Character*)actor)->getTarget()->takeDamage(getAttackDamage());
		if(((Character*)actor)->getTarget()->getHealth() == 0)
		{
			((Character*)actor)->getTarget() = NULL;
		}
	}*/
	int rand = std::rand() % 2;
	if(rand == 1)
	{
		((Character*)actor)->takeDamage(((Character*)actor)->getTarget(), ((Character*)actor)->getHealth());
	}
	else
	{
		((Character*)actor)->getTarget()->takeDamage((Character*)actor, ((Character*)actor)->getTarget()->getHealth());
		((Character*)actor)->setTarget(NULL);
	}
}

unsigned int AttackState::getAttackDamage()
{
	return std::rand() % (unsigned int)*actor->getBehavioralConfig()->get("maxattack") + 1;
}
