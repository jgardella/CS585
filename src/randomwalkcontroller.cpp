#include "randomwalkcontroller.hh"
#include <string>

RandomWalkController::RandomWalkController(DynamicArray<Actor*> *actors)
{
	Debug::getInstance()->log("WALKCONTROLLER", "Constructing RandomWalkController.");
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
		Debug::getInstance()->log("WALKCONTROLLER", "Moving actors.");
		for(i = 0; i < actors->length() && !(*actors->get(i))->isMarkedForRemoval(); i++)
		{
			// movement
			actor = *actors->get(i);
			int newX = actor->getX() + std::rand() % 5 - 2;
			int newY = actor->getY() + std::rand() % 5 - 2;
			actor->setX(newX);
			actor->setY(newY);
			Debug::getInstance()->log("GAMEPLAY", actor->getName() + " moving.");
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
						Debug::getInstance()->log("GAMEPLAY", actor->getName() + " collided with " +  collidingActor->getName() + "!");
					}
				}
			}
			delete colliders;
		}
		timeCounter = 0;
		Debug::getInstance()->log("WALKCONTROLLER", "Removing actors with collisions.");
		for(i = 0; i < actors->length(); i++)
		{
			if((*actors->get(i))->isMarkedForRemoval())
			{
				Debug::getInstance()->log("WALKCONTROLLER", actor->getName() + " had a collision, removing from the scene."); 
				SceneManager::getInstance()->removeSceneNode(actor->getSceneNode());
				delete actors->remove(i--);
			}
		}
	}
}
