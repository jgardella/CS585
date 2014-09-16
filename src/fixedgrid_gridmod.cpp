#include "fixedgrid.hh"

void FixedGrid::addSceneNode(SceneNode *node)
{
	Debug::log("FIXEDGRID", "Adding scene node.");
	int gridIndex = node->getY() *  yDimension + node->getX();
	SceneNode *nodeAtGridIndex;
	if(nodeGrid[gridIndex] == NULL) // if position in grid is empty, simply add node
	{
		nodeGrid[gridIndex] = node;
	}
	else // if position in grid is not empty, navigate to end of doubly linked list and add at end
	{
		nodeAtGridIndex = nodeGrid[gridIndex];
		while(nodeAtGridIndex->getNext() != NULL)
		{
			nodeAtGridIndex = nodeAtGridIndex->getNext();
		}
		nodeAtGridIndex->setNext(node);
	}
}

void FixedGrid::removeSceneNode(SceneNode *node)
{
	Debug::log("FIXEDGRID", "Removing scene node.");
	if(node->getPrevious() != NULL)
	{
		node->getPrevious()->setNext(node->getNext());
	}
	else
	{
		nodeGrid[node->getY() * yDimension + node->getX()] = node->getNext();
	}
	if(node->getNext() != NULL)
	{
		node->getNext()->setPrevious(node->getPrevious());
	}
}

void FixedGrid::updateSceneNode(SceneNode *node, int x, int y)
{
	Debug::log("FIXEDGRID", "Updating scene node.");
	if(x < xDimension && x >= 0 && y < yDimension && y >= 0)
	{
		Debug::log("FIXEDGRID", "New position for scene node is within bounds of scene.");
		removeSceneNode(node);
		node->setX(x);
		node->setY(y);
		addSceneNode(node);
	}
}
