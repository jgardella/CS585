#include "randomwalkcontroller.hh"

RandomWalkController::RandomWalkController(DynamicArray<Actor*> *actors, ISceneGraph *graph)
{
	this->actors = actors;
	this->graph = graph;
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
		int randXChange = std::rand() % ((int)dt) - (((int)dt) - 1) / 2;
		int randYChange = std::rand() % ((int)dt) - (((int)dt) - 1) / 2;
		SceneNode *node = actors->get(i)->getSceneNode();
		node->setX(node->getX() + randXChange);
		node->setY(node->getY() + randYChange);
	}
}
