#include "buyarmorstate.hh"

BuyArmorState::BuyArmorState(Character* character) : IState(character)
{
	this->character = character;
	isShopping = false;
	blacksmith = LevelManager::getInstance()->getBlacksmith(character->getTeam());
}

void BuyArmorState::tick(float dt)
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
			SceneManager::getInstance()->updateSceneNode(character->getSceneNode(), pos->x, pos->y);
			LevelManager::getInstance()->changePlayerGold((int)(blacksmith->getProperty("bronzecost") * blacksmith->getProperty("taxrate")));
			character->setArmor(ArmorFactory::get("bronze"));
			character->setGold(character->getGold() - (int)blacksmith->getProperty("bronzecost"));
			isShopping = true;
		}
		else
		{
			moveToBlacksmith();
		}
	}
}

void BuyArmorState::moveToBlacksmith()
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
