#include "buypotionstate.hh"

BuyPotionState::BuyPotionState(Character* character) : IState(character)
{
	this->character = character;
	isShopping = false;
	// somehow get apothecary for character
}

void BuyPotionState::tick(float dt)
{
	tPosition* pos;
	if(isShopping)
	{
		isShopping = false;
		SceneManager::getInstance()->updateSceneNode(character->getSceneNode(), apothecary->getEntranceX(), apothecary->getEntranceY());
		dispatcher->dispatch(new StateEvent("patrol"));
	}
	else
	{
		if(character->getX() == apothecary->getEntranceX() && character->getY() == apothecary->getEntranceY())
		{
			pos = apothecary->getNextAvailablePosition();
			SceneManager::getInstance()->updateSceneNode(character->getSceneNode(), pos->x, pos->y);
			LevelManager::getInstance()->changePlayerGold((int)(apothecary->getProperty("lessercost") * apothecary->getProperty("taxrate")));
			character->setPotion(HealthPotionFactory::get("lesser"));
			character->setGold(character->getGold() - (int)apothecary->getProperty("lessercost"));
			isShopping = true;
		}
		else
		{
			moveToApothecary();
		}
	}
}

void BuyPotionState::moveToApothecary()
{
	int xDist = ((Character*)actor)->getX() - apothecary->getEntranceX();
	int yDist = ((Character*)actor)->getY() - apothecary->getEntranceY();
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
