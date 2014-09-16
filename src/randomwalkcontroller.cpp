#include "randomwalkcontroller.hh"
#include <string>

RandomWalkController::RandomWalkController(DynamicArray<Actor*> *actors)
{
	Debug::log("WALKCONTROLLER", "Constructing RandomWalkController.");
	this->actors = actors;
	this->timeCounter = 0;
}

void RandomWalkController::tick(float dt)
{
	unsigned int i;
	unsigned int j;
	DynamicArray<SceneNode*> *colliders;
	timeCounter += dt;
	if(timeCounter >= 2)
	{
		Debug::log("WALKCONTROLLER", "Moving actors.");
		for(i = 0; i < actors->length(); i++)
		{
			// movement
			SceneNode *node = actors->get(i)->getSceneNode();
			int newX = node->getX() + std::rand() % 5 - 2;
			int newY = node->getY() + std::rand() % 5 - 2;
			graph->updateSceneNode(node, newX, newY);
			Debug::log(Debug::GAMEPLAY, actors->get(i)->getName() + " moving.");
			// collision
			colliders = graph->getColliders(actors->get(i)->getSceneNode());
			if(colliders->length() > 1)
			{
				for(j = 0; j < colliders->length(); j++)
				{
					colliders->remove(j)->deleteNode();
				}
				actors->get(i)->getSceneNode()->deleteNode();
			}
		}
		timeCounter = 0;
		Debug::log("WALKCONTROLLER", "Removing actors with collisions.");
		for(i = 0; i < actors->length(); i++)
		{
			if(actors->get(i)->getSceneNode()->isReadyForDeletion())
			{
				Debug::log(Debug::GAMEPLAY, actors->get(i)->getName() + " had a collision, removing from the scene."); 
				delete actors->remove(i--);
			}
		}
	}
}

void RandomWalkController::setGraph(ISceneGraph *graph)
{
	this->graph = graph;
}
