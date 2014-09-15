#include "iscenegraph.hh"

FixedGraph::FixedGraph()
{
	nodeGrid = new SceneNode[100];
	this-yDimension = 10;
}

FixedGraph::FixedGraph(int xDimension, int yDimension)
{
	nodeGrid = new SceneNode[xDimension * y Dimension];
	this->yDimension = yDimension;
}
