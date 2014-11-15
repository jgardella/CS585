#include "movetostate.hh"

void MoveToState::tick(float dt)
{
	moveToMoveLocation();
	dispatcher->tick(dt);
}

void MoveToState::moveToMoveLocation()
{
	DEBUG_LOG("MOVETOSTATE", "Moving toward move location."); 
	tPosition* moveLocation = ((Character*)actor)->getMoveLocation();
	int xDist = ((Character*)actor)->getX() - moveLocation->x;
	int yDist = ((Character*)actor)->getY() - moveLocation->y;
	int newX = ((Character*)actor)->getX();
	int newY = ((Character*)actor)->getY();
	if(yDist < 0)
	{
		newY += 1;
	}
	else if(yDist > 0)
	{
		newY -= 1;
	}
	if(xDist < 0)
	{
		newX += 1;
	}
	else if(xDist > 0)
	{
		newX -= 1;
	}
	DEBUG_LOG("MOVETOSTATE", "Moving to (" + std::to_string(newX) + ", " + std::to_string(newY) + ").");
	SceneManager::getInstance()->updateSceneNode(((Character*)actor)->getSceneNode(), newX, newY);
	if(newX == moveLocation->x && newY == moveLocation->y)
	{
		((Character*)actor)->nullifyMoveLocation();
		dispatcher->dispatch(new StateEvent("patrol"));
	}
}
