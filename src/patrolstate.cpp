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
		if(character->getType().compare(character->getType()) != 0)
		{
			DEBUG_LOG("GAMEPLAY", "Character switching to attack state.");
			dispatcher->dispatch(new StateEvent("attack"));
			return;
		}
	}
	std::srand(time(NULL));
	int newX = character->getX() + std::rand() % 3 - 1;
	int newY = character->getY() + std::rand() % 3 - 1;
	DEBUG_LOG("GAMEPLAY", "Character moving to (" + std::to_string(newX) + ", " + std::to_string(newY) + ")");
	SceneManager::getInstance()->updateSceneNode(character->getSceneNode(), newX, newY);
}
