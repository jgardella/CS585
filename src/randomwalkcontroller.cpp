#include "randomwalkcontroller.hh"

RandomWalkController::RandomWalkController(DynamicArray<Actor> *actors)
{
	this->actors = actors;
}

void RandomWalkController:tick(float dt)
{
	int i;
	for(i = 0; i < actors->length(); i++)
	{
		int randXChange = rand() % ((int)dt) - (((int)dt) - 1) / 2;
		int randYChange = rand() % ((int)dt) - (((int)dt) - 1) / 2;
		Actor actor = actors->get(i);
		actor->setX(actor->getX() + randXChange);
		actor->setY(actor->getY() + randYChange);
	}
}
