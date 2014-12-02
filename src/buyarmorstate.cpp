#include "buyarmorstate.hh"

BuyArmorState::BuyArmorState(Character* character) : IState(character)
{
	this->character = character;
	isShopping = false;
}

void BuyArmorState::tick(float dt)
{
	tPosition* pos;
	if(isShopping)
	{
		isShopping = false;
		SceneManager::getInstance()->updateSceneNode(character->getSceneNode(), LevelManager::getInstance()->getBlacksmith(character->getTeam())->getEntranceX(), LevelManager::getInstance()->getBlacksmith(character->getTeam())->getEntranceY());
		dispatcher->dispatch(new StateEvent("patrol"));
	}
	else
	{
		if(character->getX() == LevelManager::getInstance()->getBlacksmith(character->getTeam())->getEntranceX() && character->getY() == LevelManager::getInstance()->getBlacksmith(character->getTeam())->getEntranceY())
		{
			pos = LevelManager::getInstance()->getBlacksmith(character->getTeam())->getNextAvailablePosition();
			if(pos != NULL)
			{
				SceneManager::getInstance()->updateSceneNode(character->getSceneNode(), pos->x, pos->y);
				buyArmor();
				isShopping = true;
			}
		}
		else
		{
			moveToBlacksmith();
		}
	}
	dispatcher->tick(dt);
}

void BuyArmorState::moveToBlacksmith()
{
	int xDist = ((Character*)actor)->getX() - LevelManager::getInstance()->getBlacksmith(character->getTeam())->getEntranceX();
	int yDist = ((Character*)actor)->getY() - LevelManager::getInstance()->getBlacksmith(character->getTeam())->getEntranceY();
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

void BuyArmorState::buyArmor()
{
	int armQuality = character->getArmor()->getQuality();
	if(armQuality == 0)
	{
		LevelManager::getInstance()->changePlayerGold((int)(LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("bronzecost") * LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("taxrate")));
		character->setArmor(ArmorFactory::get("bronze"));
		character->setGold(character->getGold() - (int)LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("bronzecost"));
	}
	if(armQuality == 1 && LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("armorlevel") >= 2)
	{
		LevelManager::getInstance()->changePlayerGold((int)(LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("ironcost") * LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("taxrate")));
		character->setArmor(ArmorFactory::get("iron"));
		character->setGold(character->getGold() - (int)LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("ironcost"));
	}
	if(armQuality == 2 && LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("armorlevel") >= 3)
	{
		LevelManager::getInstance()->changePlayerGold((int)(LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("steelcost") * LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("taxrate")));
		character->setArmor(ArmorFactory::get("steel"));
		character->setGold(character->getGold() - (int)LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("steelcost"));
	}
}
