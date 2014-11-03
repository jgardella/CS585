#include "patrolstate.hh"

void PatrolState::tick(float dt)
{
	unsigned int i;
	Character* character;
	int radius = (int) *behavioralConfig->get("radius");
	DynamicArray<SceneNode*>* nodes = SceneManager::getInstance()->getColliders(((Character*)actor)->getX(), ((Character*)actor)->getY(), radius); 
	for(i = 0; i < nodes->length(); i++)
	{
		character = (Character*)(*nodes->get(i))->getActor();
		if(((Character*)actor)->getType().compare(character->getType()) != 0)
		{
			DEBUG_LOG("GAMEPLAY", "Character #" + std::to_string(((Character*)actor)->getID()) + " switching to attack state.");
			DEBUG_LOG("PATROLSTATE", "Character #" + std::to_string(((Character*)actor)->getID()) + " switching to attack state.");
			dispatcher->dispatch(new StateEvent("attack"));
			return;
		}
	}
	int newX = ((Character*)actor)->getX() + std::rand() % 3 - 1;
	int newY = ((Character*)actor)->getY() + std::rand() % 3 - 1;
	DEBUG_LOG("GAMEPLAY", "Character # " + std::to_string(((Character*)actor)->getID()) + " moving to (" + std::to_string(newX) + ", " + std::to_string(newY) + ").");
	SceneManager::getInstance()->updateSceneNode(((Character*)actor)->getSceneNode(), newX, newY);
}
