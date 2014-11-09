#include "building.hh"

Building::Building(unsigned int corner1X, unsigned int corner1Y, unsigned int corner2X, unsigned int corner2Y, unsigned int teamNum, unsigned int entranceX, unsigned int entranceY) : IActor(1, "building", NULL)
{
	unsigned int i;
	this->teamNum = teamNum;
	this->entranceX = entranceX;
	this->entranceY = entranceY;
	this->sceneNodes = new DynamicArray<SceneNode*>();
	for(i = corner1X; i <= corner2X; i++)
	{
		sceneNodes->pushBack(new SceneNode(i, corner1Y, *this, NULL, NULL));
		sceneNodes->pushBack(new SceneNode(i, corner2Y, *this, NULL, NULL));
	}

	for(i = corner1Y + 1; i < corner2Y; i++)
	{
		sceneNodes->pushBack(new SceneNode(corner1X, i, *this, NULL, NULL));
		sceneNodes->pushBack(new SceneNode(corner2X, i, *this, NULL, NULL));
	}
}

unsigned int Building::getTeamNumber()
{
	return teamNum;
}

void Building::getEntrance(int& x, int& y)
{
	x = entranceX;
	y = entranceY;
}
