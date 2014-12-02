#include "buypotionstate.hh"

BuyPotionState::BuyPotionState(Character* character) : IState(character)
{
	this->character = character;
	isShopping = false;
}

void BuyPotionState::tick(float dt)
{
	tPosition* pos;
	if(isShopping)
	{
		isShopping = false;
		SceneManager::getInstance()->updateSceneNode(character->getSceneNode(), LevelManager::getInstance()->getApothecary(character->getTeam())->getEntranceX(), LevelManager::getInstance()->getApothecary(character->getTeam())->getEntranceY());
		dispatcher->dispatch(new StateEvent("patrol"));
	}
	else
	{
		if(character->getX() == LevelManager::getInstance()->getApothecary(character->getTeam())->getEntranceX() && character->getY() == LevelManager::getInstance()->getApothecary(character->getTeam())->getEntranceY())
		{
			pos = LevelManager::getInstance()->getApothecary(character->getTeam())->getNextAvailablePosition();
			if(pos != NULL)
			{
				SceneManager::getInstance()->updateSceneNode(character->getSceneNode(), pos->x, pos->y);
				buyPotion();
				isShopping = true;
			}
		}
		else
		{
			moveToApothecary();
		}
	}
	dispatcher->tick(dt);
}

void BuyPotionState::moveToApothecary()
{
	int xDist = ((Character*)actor)->getX() - LevelManager::getInstance()->getApothecary(character->getTeam())->getEntranceX();
	int yDist = ((Character*)actor)->getY() - LevelManager::getInstance()->getApothecary(character->getTeam())->getEntranceY();
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
	if(character->getGold() >= LevelManager::getInstance()->getApothecary(character->getTeam())->getProperty("lessercost"))
	{
		LevelManager::getInstance()->changePlayerGold((int)(LevelManager::getInstance()->getApothecary(character->getTeam())->getProperty("lessercost") * LevelManager::getInstance()->getApothecary(character->getTeam())->getProperty("taxrate")));
		character->setPotion(HealthPotionFactory::get("lesser"));
		MenuManager::getInstance()->setAlertString(character->getType() + " #" + std::to_string(character->getID()) + " bought a lesser health potion.");
		character->setGold(character->getGold() - (int)LevelManager::getInstance()->getApothecary(character->getTeam())->getProperty("lessercost"));
	}
	if(character->getGold() >= LevelManager::getInstance()->getApothecary(character->getTeam())->getProperty("moderatecost") && LevelManager::getInstance()->getApothecary(character->getTeam())->getProperty("level") == 2)
	{
		LevelManager::getInstance()->changePlayerGold((int)(LevelManager::getInstance()->getApothecary(character->getTeam())->getProperty("moderatecost") * LevelManager::getInstance()->getApothecary(character->getTeam())->getProperty("taxrate")));
		character->setPotion(HealthPotionFactory::get("moderate"));
		MenuManager::getInstance()->setAlertString(character->getType() + " #" + std::to_string(character->getID()) + " bought a moderate health potion.");
		character->setGold(character->getGold() - (int)LevelManager::getInstance()->getApothecary(character->getTeam())->getProperty("moderatecost"));
	}
	if(character->getGold() >= LevelManager::getInstance()->getApothecary(character->getTeam())->getProperty("severecost") && LevelManager::getInstance()->getApothecary(character->getTeam())->getProperty("level") == 3)
	{
		LevelManager::getInstance()->changePlayerGold((int)(LevelManager::getInstance()->getApothecary(character->getTeam())->getProperty("severecost") * LevelManager::getInstance()->getApothecary(character->getTeam())->getProperty("taxrate")));
		character->setPotion(HealthPotionFactory::get("severe"));
		MenuManager::getInstance()->setAlertString(character->getType() + " #" + std::to_string(character->getID()) + " bought a severe health potion.");
		character->setGold(character->getGold() - (int)LevelManager::getInstance()->getApothecary(character->getTeam())->getProperty("severecost"));
	}
}
