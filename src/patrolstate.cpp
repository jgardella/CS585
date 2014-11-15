#include "patrolstate.hh"

void PatrolState::tick(float dt)
{
	int newX, newY;
	unsigned int i;
	Character* character;
	int radius = (int) *actor->getBehavioralConfig()->get("radius");
	DynamicArray<SceneNode*>* nodes = SceneManager::getInstance()->getColliders(((Character*)actor)->getX(), ((Character*)actor)->getY(), radius); 
	for(i = 0; i < nodes->length(); i++)
	{
		character = (Character*)(*nodes->get(i))->getActor();
		DEBUG_LOG("PATROLSTATE", "Character #" + std::to_string(((Character*)actor)->getID()) + " can attack Character #" + std::to_string(character->getID()) + ".");
		if(((Character*)actor)->getType().compare(character->getType()) != 0)
		{
			DEBUG_LOG("PATROLSTATE", "Character #" + std::to_string(((Character*)actor)->getID()) + " switching to attack state.");
			dispatcher->dispatch(new StateEvent("attack"));
			return;
		}
	}
	if(((Character*)actor)->getMoveLocation() != NULL)
	{
		moveToMoveLocation();
	}
	else
	{
		do
		{
			newX = ((Character*)actor)->getX() + std::rand() % 3 - 1;
			newY = ((Character*)actor)->getY() + std::rand() % 3 - 1;
		}
		while(SceneManager::getInstance()->getColliders(newX, newY, true)->length() != 0); // randomize position until it is unoccupied
		DEBUG_LOG("GAMEPLAY", "Character # " + std::to_string(((Character*)actor)->getID()) + " moving to (" + std::to_string(newX) + ", " + std::to_string(newY) + ").");
		SceneManager::getInstance()->updateSceneNode(((Character*)actor)->getSceneNode(), newX, newY);
	}
	dispatcher->tick(dt);
}

void PatrolState::moveToMoveLocation()
{
	DEBUG_LOG("PATROLSTATE", "Moving toward move location."); 
	tPosition* moveLocation = ((Character*)actor)->getMoveLocation();
	int xDist = ((Character*)actor)->getX() - moveLocation->x;
	int yDist = ((Character*)actor)->getY() - moveLocation->y;
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
	DEBUG_LOG("PATROLSTATE", "Moving to (" + std::to_string(newX) + ", " + std::to_string(newY) + ").");
	SceneManager::getInstance()->updateSceneNode(((Character*)actor)->getSceneNode(), newX, newY);
	if(newX == moveLocation->x && newY == moveLocation->y)
	{
		((Character*)actor)->nullifyMoveLocation();
	}
}
