#include "drinkstate.hh"

DrinkState::DrinkState(Character* character) : IState(character)
{
	this->character = character;
	home = LevelManager::getInstance()->getHome(character->getTeam());
	isDrinking = false;
}

void DrinkState::tick(float dt)
{
	tPosition* pos;
	if(isDrinking)
	{
		character->drink();
		if(character->hasMaxHydration())
		{
			SceneManager::getInstance()->updateSceneNode(character->getSceneNode(), home->getEntranceX(), home->getEntranceY());
			isDrinking = false;
			dispatcher->dispatch(new StateEvent("patrol"));
		}
	}
	else
	{
		if(home->getEntranceX() == character->getX() && home->getEntranceY() == character->getY())
		{
			pos = home->getNextAvailablePosition();
			SceneManager::getInstance()->updateSceneNode(character->getSceneNode(), pos->x, pos->y);
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
	int xDist = character->getX() - home->getEntranceX();
	int yDist = character->getY() - home->getEntranceY();
	int newX = character->getX();
	int newY = character->getY();
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
	SceneManager::getInstance()->updateSceneNode(character->getSceneNode(), newX, newY);
}

void DrinkState::buyDrink()
{
	if(character->getGold() >= home->getProperty("lessercost"))
	{
		DEBUG_LOG("DRINKSTATE", "Changing player gold by amount: " + std::to_string((int)(home->getProperty("lessercost") * home->getProperty("taxrate"))));
		LevelManager::getInstance()->changePlayerGold((int)(home->getProperty("lessercost") * home->getProperty("taxrate")));
		((Character*)actor)->setGold(((Character*)actor)->getGold() - (int)home->getProperty("lessercost"));
	}
	if(character->getGold() >= home->getProperty("averagecost") && home->getProperty("level") >= 2)
	{
		DEBUG_LOG("DRINKSTATE", "Changing player gold by amount: " + std::to_string((int)(home->getProperty("averagecost") * home->getProperty("taxrate"))));
		LevelManager::getInstance()->changePlayerGold((int)(home->getProperty("averagecost") * home->getProperty("taxrate")));
		((Character*)actor)->setGold(((Character*)actor)->getGold() - (int)home->getProperty("averagecost"));
	}
	if(character->getGold() >= home->getProperty("mastercost") && home->getProperty("level") >= 3)
	{
		DEBUG_LOG("DRINKSTATE", "Changing player gold by amount: " + std::to_string((int)(home->getProperty("mastercost") * home->getProperty("taxrate"))));
		LevelManager::getInstance()->changePlayerGold((int)(home->getProperty("mastercost") * home->getProperty("taxrate")));
		((Character*)actor)->setGold(((Character*)actor)->getGold() - (int)home->getProperty("mastercost"));
	}
}
