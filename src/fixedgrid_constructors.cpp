#include "fixedgrid.hh"

FixedGrid::FixedGrid()
{
	nodeGrid = new SceneNode[100];
	this->yDimension = 10;
}

FixedGrid::FixedGrid(int xDimension, int yDimension)
{
	nodeGrid = new SceneNode[xDimension * yDimension];
	this->yDimension = yDimension;
}
