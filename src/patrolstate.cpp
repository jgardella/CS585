#include "patrolstate.hh"

PatrolState::PatrolState(Character* character) : IState(character)
{
	this->character = character;
	this->home = LevelManager::getInstance()->getHome(character->getTeam());
}

void PatrolState::tick(float dt)
{
	int newX, newY;
	unsigned int i;
	Character* otherCharacter;
	int radius = (int) *character->getBehavioralConfig()->get("radius");
	DEBUG_LOG("PATROLSTATE", "Radius: " + std::to_string(radius));
	DynamicArray<SceneNode*>* nodes = SceneManager::getInstance()->getColliders(character->getX(), character->getY(), radius); 
	DEBUG_LOG("PATROLSTATE", "Number of colliders: " + std::to_string(nodes->length()));
	for(i = 0; i < nodes->length(); i++)
	{
		if((*nodes->get(i))->getActor()->getClass().compare("CHARACTER") == 0)
		{
			otherCharacter = (Character*)(*nodes->get(i))->getActor();
			DEBUG_LOG("PATROLSTATE", "Character #" + std::to_string(((Character*)actor)->getID()) + " can attack Character #" + std::to_string(character->getID()) + ".");
			if(character->getTeam() != otherCharacter->getTeam() && !character->isDead())
			{
				DEBUG_LOG("PATROLSTATE", "Character #" + std::to_string(character->getID()) + " switching to attack state.");
				dispatcher->dispatch(new StateEvent("attack"));
				dispatcher->tick(dt);
				return;
			}
		}
	}
	do
	{
		newX = character->getX() + std::rand() % 3 - 1;
		newY = character->getY() + std::rand() % 3 - 1;
	}
	while(SceneManager::getInstance()->getColliders(newX, newY, true)->length() != 0); // randomize position until it is unoccupied
	DEBUG_LOG("GAMEPLAY", "Character # " + std::to_string(character->getID()) + " moving to (" + std::to_string(newX) + ", " + std::to_string(newY) + ").");
	SceneManager::getInstance()->updateSceneNode(((Character*)actor)->getSceneNode(), newX, newY);
	// check energy and hydration levels
	if(character->getType().compare("dwarf") == 0)
	{
		if(character->getEnergy() <= character->getProperty("energythres"))
		{
			DEBUG_LOG("PATROLSTATE", "Character switching to sleep state.");
			dispatcher->dispatch(new StateEvent("sleep"));
		}
		else if(character->getHydration() <= character->getProperty("hydrationthres")
				&& character->getGold() >= home->getProperty("lessercost"))
		{
			DEBUG_LOG("PATROLSTATE", "Character switching to drink state.");
			dispatcher->dispatch(new StateEvent("drink"));
		}
		else if(LevelManager::getInstance()->isBlacksmithBuilt())
		{
			if(hasEnoughGoldForNextWeapon())
			{
				DEBUG_LOG("PATROLSTATE", "Character switching to buy weapon state.");
				dispatcher->dispatch(new StateEvent("buyweapon"));
			}
		}
		else if(LevelManager::getInstance()->isBlacksmithBuilt())
		{
			if(hasEnoughGoldForNextArmor())
			{
				DEBUG_LOG("PATROLSTATE", "Character switching to buy armor state.");
				dispatcher->dispatch(new StateEvent("buyarmor"));
			}
		}
		else if(LevelManager::getInstance()->isApothecaryBuilt() && character->getGold() >= LevelManager::getInstance()->getApothecary(character->getTeam())->getProperty("lessercost") && character->getPotion() == NULL)
		{
			DEBUG_LOG("PATROLSTATE", "Character switching to buy potion state.");
			dispatcher->dispatch(new StateEvent("buypotion"));
		}
	}
	dispatcher->tick(dt);
}

bool PatrolState::hasEnoughGoldForNextWeapon()
{
	Building* blacksmith = LevelManager::getInstance()->getBlacksmith(character->getTeam());
	int weapQuality = character->getWeapon()->getQuality();
	if(weapQuality == 0)
	{
		return character->getGold() >= blacksmith->getProperty("daggercost");
	}
	if(weapQuality == 1)
	{
		return character->getGold() >= blacksmith->getProperty("swordcost");
	}
	if(weapQuality == 2)
	{
		return character->getGold() >= blacksmith->getProperty("warhammercost");
	}
	return false;
}

bool PatrolState::hasEnoughGoldForNextArmor()
{
	Building* blacksmith = LevelManager::getInstance()->getBlacksmith(character->getTeam());
	int armQuality = character->getArmor()->getQuality();
	if(armQuality == 0)
	{
		return character->getGold() >= blacksmith->getProperty("bronzecost");
	}
	if(armQuality == 1)
	{
		return character->getGold() >= blacksmith->getProperty("ironcost");
	}
	if(armQuality == 2)
	{
		return character->getGold() >= blacksmith->getProperty("steelcost");
	}
	return false;
}
