#include "randomwalkcontroller.hh"

RandomWalkController::RandomWalkController(DynamicArray<Actor*> *actors)
{
	this->actors = actors;
}

void RandomWalkController::tick(float dt)
{
	unsigned int i;
	for(i = 0; i < actors->length(); i++)
	{
		int randXChange = std::rand() % ((int)dt) - (((int)dt) - 1) / 2;
		int randYChange = std::rand() % ((int)dt) - (((int)dt) - 1) / 2;
		SceneNode *node = actors->get(i)->getSceneNode();
		node->setX(node->getX() + randXChange);
		node->setY(node->getY() + randYChange);
	}
}
