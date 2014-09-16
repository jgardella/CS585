#include "randomwalkcontroller.hh"
#include <string>

RandomWalkController::RandomWalkController(DynamicArray<Actor*> *actors)
{
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
		for(i = 0; i < actors->length(); i++)
		{
			colliders = graph->getColliders(actors->get(i)->getSceneNode());
			if(colliders->length() > 1)
			{
				for(j = 0; j < colliders->length(); j++)
				{
					Debug::log(Debug::GAMEPLAY, "Removing collision");
					delete colliders->get(j);
				}
			}
			else
			{
				SceneNode *node = actors->get(i)->getSceneNode();
				int newX = node->getX() + std::rand() % 5 - 2;
				int newY = node->getY() + std::rand() % 5 - 2;
				graph->updateSceneNode(node, newX, newY);
				Debug::log(Debug::GAMEPLAY, actors->get(i)->getName() + " moving.");
				std::cout << " to (" << newX << ", " << newY << ")" << std::endl;
			}
		}
		timeCounter = 0;
	}
}

void RandomWalkController::setGraph(ISceneGraph *graph)
{
	this->graph = graph;
}
