#include "fixedgrid.hh"

FixedGrid::FixedGrid()
{
	DEBUG_LOG("FIXEDGRID", "Constructing fixed grid with default dimensions 10x10.");
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
	DEBUG_LOG("FIXEDGRID", "Constructing fixed grid with dimension " + std::to_string(xDimension) + "x" + std::to_string(yDimension) + ".");
	int i;
	long size = xDimension * yDimension;
	nodeGrid = new SceneNode*[size];
	for(i = 0; i < size; i++)
	{
		nodeGrid[i] = NULL;
	}
	this->yDimension = yDimension;
	this->xDimension = xDimension;
}
