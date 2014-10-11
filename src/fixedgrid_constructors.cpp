#include "fixedgrid.hh"

FixedGrid::FixedGrid()
{
	DEBUG_LOG("FIXEDGRID", "Constructing fixed grid.");
	int i;
	nodeGrid = new SceneNode*[100];
	for(i = 0; i < 100; i++)
	{
		nodeGrid[i] = NULL;
	}
	this->yDimension = 10;
	this->xDimension = 10;
}

FixedGrid::FixedGrid(int xDimension, int yDimension)
{
	DEBUG_LOG("FIXEDGRID", "Constructing fixed grid.");
	int i;
	nodeGrid = new SceneNode*[xDimension * yDimension];
	for(i = 0; i < 100; i++)
	{
		nodeGrid[i] = NULL;
	}
	this->yDimension = yDimension;
	this->xDimension = xDimension;
}
