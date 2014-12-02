#include "buypotionstate.hh"

BuyPotionState::BuyPotionState(Character* character) : IState(character)
{
	this->character = character;
	isShopping = false;
	apothecary = LevelManager::getInstance()->getApothecary(character->getTeam());
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
			buyPotion();
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

void BuyPotionState::buyPotion()
{
	if(character->getGold() >= apothecary->getProperty("lessercost"))
	{
		LevelManager::getInstance()->changePlayerGold((int)(apothecary->getProperty("lessercost") * apothecary->getProperty("taxrate")));
		character->setPotion(HealthPotionFactory::get("lesser"));
		character->setGold(character->getGold() - (int)apothecary->getProperty("lessercost"));
	}
	if(character->getGold() >= apothecary->getProperty("moderatecost") && apothecary->getProperty("level") == 2)
	{
		LevelManager::getInstance()->changePlayerGold((int)(apothecary->getProperty("moderatecost") * apothecary->getProperty("taxrate")));
		character->setPotion(HealthPotionFactory::get("moderate"));
		character->setGold(character->getGold() - (int)apothecary->getProperty("moderatecost"));
	}
	if(character->getGold() >= apothecary->getProperty("severecost") && apothecary->getProperty("level") == 3)
	{
		LevelManager::getInstance()->changePlayerGold((int)(apothecary->getProperty("severecost") * apothecary->getProperty("taxrate")));
		character->setPotion(HealthPotionFactory::get("severe"));
		character->setGold(character->getGold() - (int)apothecary->getProperty("severecost"));
	}
}
