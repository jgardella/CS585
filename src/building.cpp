#include "building.hh"

Building::Building(std::string type, unsigned int corner1X, unsigned int corner1Y, unsigned int teamNum, Trie<double>* behavioralConfig, BuildingFunction* function) : IActor(1, "BUILDING", behavioralConfig)
{
	unsigned int i;
	unsigned int width = *behavioralConfig->get("width");
	unsigned int height = *behavioralConfig->get("height");
	this->teamNum = teamNum;
	this->sceneNodes = new DynamicArray<SceneNode*>();
	this->type = type;
	this->corner1X = corner1X;
	this->corner1Y = corner1Y;
	this->entranceX = corner1X + width/2;
	this->entranceY = corner1Y - 1;
	for(i = corner1X; i <= width + corner1X; i++)
	{
		sceneNodes->pushBack(new SceneNode(i, corner1Y, *this, NULL, NULL));
		sceneNodes->pushBack(new SceneNode(i, corner1Y + width, *this, NULL, NULL));
	}

	for(i = corner1Y + 1; i < height + corner1Y; i++)
	{
		sceneNodes->pushBack(new SceneNode(corner1X, i, *this, NULL, NULL));
		sceneNodes->pushBack(new SceneNode(corner1X + height, i, *this, NULL, NULL));
	}
	
	this->function = function;

	setType(type);
}

unsigned int Building::getTeamNumber()
{
	return teamNum;
}

DynamicArray<SceneNode*>* Building::getSceneNodes()
{
	return sceneNodes;
}

std::string Building::inspect()
{
	return type;
}

bool Building::sendKeyPress(int key, int cursorX, int cursorY)
{
	return function->parseKeyPress(key, cursorX, cursorY);
}

int Building::getEntranceX()
{
	return entranceX;
}

int Building::getEntranceY()
{
	return entranceY;
}

tPosition* Building::getNextAvailablePosition()
{
	unsigned int i, j;
	unsigned int width = *behavioralConfig->get("width");
	unsigned int height = *behavioralConfig->get("height");
	for(i = corner1X + 1; i < width + corner1X; i++)
	{
		for(j = corner1Y + 1; j < height + corner1Y; j++)
		{
			if(SceneManager::getInstance()->getColliders(i, j, true)->length() == 0)
			{
				return new tPosition(i, j);
			}
		}
	}
	return NULL;
}
