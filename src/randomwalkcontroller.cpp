#include "randomwalkcontroller.hh"

RandomWalkController::RandomWalkController(DynamicArray<Actor*> *actors)
{
	this->actors = actors;
}

void RandomWalkController::tick(float dt)
{
	unsigned int i;
	unsigned int j;
	DynamicArray<SceneNode*> colliders;
	for(i = 0; i < actors->length(); i++)
	{
		colliders = graph->getColliders(*(actors->get(i)->getSceneNode()));
		for(j = 0; j < colliders.length(); j++)
		{
			Debug::log(Debug::GAMEPLAY, "Removing collision");
			delete colliders.get(j);
		}
		if(colliders.length() > 0)
		{
			delete actors->get(i)->getSceneNode();
		}
		int randXChange = std::rand() % 5 - 2;
		int randYChange = std::rand() % 5 - 2;
		SceneNode *node = actors->get(i)->getSceneNode();
		graph->updateSceneNode(*node, node->getX() + randXChange, node->getY() + randYChange);
	}
}

void RandomWalkController::setGraph(ISceneGraph *graph)
{
	this->graph = graph;
}
