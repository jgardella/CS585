#include "randomwalkcontroller.hh"
#include <string>

RandomWalkController::RandomWalkController(DynamicArray<Actor*> *actors)
{
	DEBUG_LOG("WALKCONTROLLER", "Constructing RandomWalkController.");
	this->actors = actors;
	this->timeCounter = 0;
}

void RandomWalkController::tick(float dt)
{
	unsigned int i;
	unsigned int j;
	DynamicArray<SceneNode*> *colliders;
	Actor* actor;
	timeCounter += dt;
	if(timeCounter >= 2)
	{
		DEBUG_LOG("WALKCONTROLLER", "Moving actors.");
		for(i = 0; i < actors->length() && !(*actors->get(i))->isMarkedForRemoval(); i++)
		{
			// movement
			actor = *actors->get(i);
			int newX = actor->getX() + std::rand() % 3 - 1;
			int newY = actor->getY() + std::rand() % 3 - 1;
			SceneManager::getInstance()->updateSceneNode(actor->getSceneNode(), newX, newY);
			DEBUG_LOG("GAMEPLAY", actor->getName() + " moving to (" + std::to_string(newX) + ", " + std::to_string(newY) + ").");
			// collision
			colliders = SceneManager::getInstance()->getColliders(actor->getSceneNode());
			if(colliders->length() > 1)
			{
				for(j = 0; j < colliders->length(); j++)
				{
					IActor* iactor = (*colliders->get(j))->getActor();
					if(iactor->getClass().compare("ACTOR") == 0 && iactor != (*actors->get(i)))
					{
						Actor* collidingActor = (Actor*) iactor;
						collidingActor->markForRemoval();
						actor->markForRemoval();
						DEBUG_LOG("GAMEPLAY", actor->getName() + " collided with " +  collidingActor->getName() + "!");
					}
				}
			}
			delete colliders;
		}
		timeCounter = 0;
		DEBUG_LOG("WALKCONTROLLER", "Removing actors with collisions.");
		for(i = 0; i < actors->length(); i++)
		{
			actor = *actors->get(i);	
			if(actor->isMarkedForRemoval())
			{
				DEBUG_LOG("WALKCONTROLLER", actor->getName() + " had a collision, removing from the scene."); 
				SceneManager::getInstance()->removeSceneNode(actor->getSceneNode());
				delete actors->remove(i--);
			}
		}
	}
}
