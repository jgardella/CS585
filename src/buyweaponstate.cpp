#include "buyweaponstate.hh"

BuyWeaponState::BuyWeaponState(Character* character) : IState(character)
{
	this->character = character;
	isShopping = false;
	blacksmith = LevelManager::getInstance()->getBlacksmith(character->getTeam());
}

void BuyWeaponState::tick(float dt)
{
	tPosition* pos;
	if(isShopping)
	{
		isShopping = false;
		SceneManager::getInstance()->updateSceneNode(character->getSceneNode(), blacksmith->getEntranceX(), blacksmith->getEntranceY());
		dispatcher->dispatch(new StateEvent("patrol"));
	}
	else
	{
		if(character->getX() == blacksmith->getEntranceX() && character->getY() == blacksmith->getEntranceY())
		{
			pos = blacksmith->getNextAvailablePosition();
			buyWeapon();
			SceneManager::getInstance()->updateSceneNode(character->getSceneNode(), pos->x, pos->y);
			isShopping = true;
		}
		else
		{
			moveToBlacksmith();
		}
	}
}

void BuyWeaponState::moveToBlacksmith()
{
	int xDist = ((Character*)actor)->getX() - blacksmith->getEntranceX();
	int yDist = ((Character*)actor)->getY() - blacksmith->getEntranceY();
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

void BuyWeaponState::buyWeapon()
{
	int weapQuality = character->getWeapon()->getQuality();
	if(weapQuality == 0)
	{
		LevelManager::getInstance()->changePlayerGold((int)(blacksmith->getProperty("daggercost") * blacksmith->getProperty("taxrate")));
		character->setWeapon(WeaponFactory::get("dagger"));
		character->setGold(character->getGold() - (int)blacksmith->getProperty("daggercost"));
	}
	if(weapQuality == 1 && blacksmith->getProperty("weaponlevel") >= 2)
	{
		LevelManager::getInstance()->changePlayerGold((int)(blacksmith->getProperty("swordcost") * blacksmith->getProperty("taxrate")));
		character->setWeapon(WeaponFactory::get("sword"));
		character->setGold(character->getGold() - (int)blacksmith->getProperty("swordcost"));
	}
	if(weapQuality == 2 && blacksmith->getProperty("weaponlevel") >= 3)
	{
		LevelManager::getInstance()->changePlayerGold((int)(blacksmith->getProperty("warhammercost") * blacksmith->getProperty("taxrate")));
		character->setWeapon(WeaponFactory::get("warhammer"));
		character->setGold(character->getGold() - (int)blacksmith->getProperty("warhammercost"));
	}
}
