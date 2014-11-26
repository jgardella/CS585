#include "drinkstate.hh"

DrinkState::DrinkState(IActor* actor) : IState(actor)
{
	home = LevelManager::getInstance()->getHome(((Character*)actor)->getTeam());
	isDrinking = false;
}

void DrinkState::tick(float dt)
{
	tPosition* pos;
	if(isDrinking)
	{
		((Character*)actor)->drink();
		if(((Character*)actor)->hasMaxHydration())
		{
			SceneManager::getInstance()->updateSceneNode(((Character*)actor)->getSceneNode(), home->getEntranceX(), home->getEntranceY());
			isDrinking = false;
			dispatcher->dispatch(new StateEvent("patrol"));
		}
	}
	else
	{
		if(home->getEntranceX() == ((Character*)actor)->getX() && home->getEntranceY() == ((Character*)actor)->getY())
		{
			pos = home->getNextAvailablePosition();
			SceneManager::getInstance()->updateSceneNode(((Character*)actor)->getSceneNode(), pos->x, pos->y);
			LevelManager::getInstance()->changePlayerGold((int)(home->getProperty("drinkcost") * home->getProperty("taxrate")));
			((Character*)actor)->setGold(((Character*)actor)->getGold() - (int)home->getProperty("drinkcost"));
			isDrinking = true;
		}
		else
		{
			moveToHome();
		}
	}
	dispatcher->tick(dt);
}

void DrinkState::moveToHome()
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
