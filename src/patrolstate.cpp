#include "patrolstate.hh"

void PatrolState::tick(float dt)
{
	unsigned int i;
	Character* character;
	int radius = (int) *behavioralConfig->get("radius");
	DynamicArray<SceneNode*>* nodes = SceneManager::getInstance()->getColliders(((Character*)actor)->getX(), ((Character*)actor)->getY(), radius); 
	DEBUG_LOG("PATROLSTATE", "Number of actors in range: " + std::to_string(nodes->length()) + ".");
	for(i = 0; i < nodes->length(); i++)
	{
		character = (Character*)(*nodes->get(i))->getActor();
		if(character->getType().compare(character->getType()) != 0)
		{
			DEBUG_LOG("GAMEPLAY", "Character switching to attack state.");
			DEBUG_LOG("PATROLSTATE", "Character switching to attack state.");
			dispatcher->dispatch(new StateEvent("attack"));
			return;
		}
	}
	int newX = ((Character*)actor)->getX() + std::rand() % 3 - 1;
	int newY = ((Character*)actor)->getY() + std::rand() % 3 - 1;
	SceneManager::getInstance()->updateSceneNode(((Character*)actor)->getSceneNode(), newX, newY);
}
