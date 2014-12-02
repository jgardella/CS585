#include "buyweaponstate.hh"

BuyWeaponState::BuyWeaponState(Character* character) : IState(character)
{
	this->character = character;
	isShopping = false;
}

void BuyWeaponState::tick(float dt)
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
				buyWeapon();
				SceneManager::getInstance()->updateSceneNode(character->getSceneNode(), pos->x, pos->y);
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

void BuyWeaponState::moveToBlacksmith()
{
	int xDist = character->getX() - LevelManager::getInstance()->getBlacksmith(character->getTeam())->getEntranceX();
	int yDist = character->getY() - LevelManager::getInstance()->getBlacksmith(character->getTeam())->getEntranceY();
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

void BuyWeaponState::buyWeapon()
{
	int weapQuality = character->getWeapon()->getQuality();
	if(weapQuality == 0)
	{
		LevelManager::getInstance()->changePlayerGold((int)(LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("daggercost") * LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("taxrate")));
		character->setWeapon(WeaponFactory::get("dagger"));
		MenuManager::getInstance()->setAlertString(character->getType() + " #" + std::to_string(character->getID()) + " bought a dagger.");
		character->setGold(character->getGold() - (int)LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("daggercost"));
	}
	if(weapQuality == 1 && LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("weaponlevel") >= 2)
	{
		LevelManager::getInstance()->changePlayerGold((int)(LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("swordcost") * LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("taxrate")));
		character->setWeapon(WeaponFactory::get("sword"));
		MenuManager::getInstance()->setAlertString(character->getType() + " #" + std::to_string(character->getID()) + " bought a sword.");
		character->setGold(character->getGold() - (int)LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("swordcost"));
	}
	if(weapQuality == 2 && LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("weaponlevel") >= 3)
	{
		LevelManager::getInstance()->changePlayerGold((int)(LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("warhammercost") * LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("taxrate")));
		character->setWeapon(WeaponFactory::get("warhammer"));
		MenuManager::getInstance()->setAlertString(character->getType() + " #" + std::to_string(character->getID()) + " bought a warhammer.");
		character->setGold(character->getGold() - (int)LevelManager::getInstance()->getBlacksmith(character->getTeam())->getProperty("warhammercost"));
	}
}
