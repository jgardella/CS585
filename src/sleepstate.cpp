#include "sleepstate.hh"

SleepState::SleepState(IActor* actor) : IState(actor)
{
	home = LevelManager::getInstance()->getHome(((Character*)actor)->getTeam());
	isSleeping = false;
}

void SleepState::tick(float dt)
{
	tPosition* pos;
	if(isSleeping)
	{
		((Character*)actor)->sleep();
		if(((Character*)actor)->hasMaxEnergy())
		{
			SceneManager::getInstance()->updateSceneNode(((Character*)actor)->getSceneNode(), home->getEntranceX(), home->getEntranceY());
			isSleeping = false;
			dispatcher->dispatch(new StateEvent("patrol"));
		}
	}
	else
	{
		if(home->getEntranceX() == ((Character*)actor)->getX() && home->getEntranceY() == ((Character*)actor)->getY())
		{
			pos = home->getNextAvailablePosition();
			SceneManager::getInstance()->updateSceneNode(((Character*)actor)->getSceneNode(), pos->x, pos->y);
			isSleeping = true;
		}
		else
		{
			int xDist = ((Character*)actor)->getX() - home->getEntranceX();
			int yDist = ((Character*)actor)->getY() - home->getEntranceY();
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
			SceneManager::getInstance()->updateSceneNode(((Character*)actor)->getSceneNode(), newX, newY);
		}
	}
	dispatcher->tick(dt);
}
