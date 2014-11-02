#include "attackstate.hh"

void AttackState::tick(float dt)
{
	if(target == NULL) // scan for target
	{
		scanForTarget();
	}
	if(target == NULL) // target not found, return to patrol
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
}

void AttackState::scanForTarget()
{
	DEBUG_LOG("ATTACKSTATE", "Scanning for target.");
	unsigned int i;
	Character* character;
	int radius = (int) *behavioralConfig->get("radius");
	DynamicArray<SceneNode*>* nodes = SceneManager::getInstance()->getColliders(((Character*)actor)->getX(), ((Character*)actor)->getY(), radius); 
	for(i = 0; i < nodes->length(); i++)
	{
		character = (Character*)(*nodes->get(i))->getActor();
		if(character->getType().compare(character->getType()) != 0)
		{
			DEBUG_LOG("ATTACKSTATE", "Found target.");
			target = character;
		}
	}
}

void AttackState::moveTowardTarget()
{
	DEBUG_LOG("ATTACKSTATE", "Moving toward target.");
	int xDist = ((Character*)actor)->getX() - target->getX();
	int yDist = ((Character*)actor)->getY() - target->getY();
	int newX = ((Character*)actor)->getX();
	int newY = ((Character*)actor)->getY();
	if(yDist < 0)
	{
		newY -= 1;
	}
	else if(yDist > 0)
	{
		newY += 1;
	}
	if(xDist < 0)
	{
		newX -= 1;
	}
	else if(xDist > 0)
	{
		newX += 1;
	}
	DEBUG_LOG("ATTACKSTATE", "Moving to (" + std::to_string(newX) + ", " + std::to_string(newY) + ").");
	SceneManager::getInstance()->updateSceneNode(((Character*)actor)->getSceneNode(), newX, newY);
}

bool AttackState::targetInRange()
{
	return std::abs(((Character*)actor)->getX() - target->getX()) == 1 && std::abs(((Character*)actor)->getY() - target->getY()) == 1;
}

void AttackState::attackTarget()
{
	DEBUG_LOG("ATTACKSTATE", "Attempting to attack target.");
	int damage;
	float rand = std::rand() / ((float) RAND_MAX);
	if(rand < *behavioralConfig->get("chance"))
	{
		damage = getAttackDamage();
		DEBUG_LOG("ATTACKSTATE", "Attacking target with damage " + std::to_string(damage) + ".");
		DEBUG_LOG("GAMEPLAY", "Attacking target with damage " + std::to_string(damage) + ".");	
		target->takeDamage(getAttackDamage());
	}
}

unsigned int AttackState::getAttackDamage()
{
	std::srand(time(NULL));
	return std::rand() % (unsigned int)*behavioralConfig->get("maxattack") + 1;
}
