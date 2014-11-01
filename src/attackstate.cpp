#include "attackstate.hh"

void AttackState::tick(float dt)
{
	if(target == NULL) // scan for target
	{
		scanForTarget();
	}
	if(target == NULL) // target not found, return to patrol
	{
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
	unsigned int i;
	Character* character;
	int radius = (int) *behavioralConfig->get("radius");
	DynamicArray<SceneNode*>* nodes = SceneManager::getInstance()->getColliders(((Character*)actor)->getX(), ((Character*)actor)->getY(), radius); 
	for(i = 0; i < nodes->length(); i++)
	{
		character = (Character*)(*nodes->get(i))->getActor();
		if(character->getType().compare(character->getType()) != 0)
		{
			target = character;
		}
	}
}

void AttackState::moveTowardTarget()
{
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
	SceneManager::getInstance()->updateSceneNode(((Character*)actor)->getSceneNode(), newX, newY);
}

bool AttackState::targetInRange()
{
	return std::abs(((Character*)actor)->getX() - target->getX()) == 1 && std::abs(((Character*)actor)->getY() - target->getY()) == 1;
}

void AttackState::attackTarget()
{
	std::srand(time(NULL));
	float rand = std::rand() / ((float) RAND_MAX);
	if(rand < *behavioralConfig->get("chance"))
	{
		target->takeDamage(getAttackDamage());
	}
}

unsigned int AttackState::getAttackDamage()
{
	std::srand(time(NULL));
	return std::rand() % (unsigned int)*behavioralConfig->get("maxattack") + 1;
}
