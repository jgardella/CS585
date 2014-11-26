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
	do
	{
		newX = ((Character*)actor)->getX() + std::rand() % 3 - 1;
		newY = ((Character*)actor)->getY() + std::rand() % 3 - 1;
	}
	while(SceneManager::getInstance()->getColliders(newX, newY, true)->length() != 0); // randomize position until it is unoccupied
	DEBUG_LOG("GAMEPLAY", "Character # " + std::to_string(((Character*)actor)->getID()) + " moving to (" + std::to_string(newX) + ", " + std::to_string(newY) + ").");
	SceneManager::getInstance()->updateSceneNode(((Character*)actor)->getSceneNode(), newX, newY);
	// check energy and hydration levels
	if(((Character*)actor)->getType().compare("dwarf") == 0)
	{
		if(((Character*)actor)->getEnergy() < ((Character*)actor)->getProperty("energythres"))
		{
			DEBUG_LOG("PATROLSTATE", "Character switching to sleep state.");
			dispatcher->dispatch(new StateEvent("sleep"));
			dispatcher->tick(1);
		}
		else if(((Character*)actor)->getHydration() < ((Character*)actor)->getProperty("hydrationthres")
				&& ((Character*)actor)->getGold() >= LevelManager::getInstance()->getHome(((Character*)actor)->getTeam())->getProperty("drinkcost"))
		{
			DEBUG_LOG("PATROLSTATE", "Character switching to drink state.");
			dispatcher->dispatch(new StateEvent("drink"));
			dispatcher->tick(1);
		}
		dispatcher->tick(dt);
	}
}
