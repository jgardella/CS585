#include "fixedgraph.hh"

void FixedGraph::addSceneNode(SceneNode node)
{
	int gridIndex = node.yCoordinate *  yDimension + node.xCoordinate;
	SceneNode *nodeAtGridIndex;
	if(nodeGrid[gridIndex] == NULL) // if position in grid is empty, simply add node
	{
		nodeGrid[gridIndex] = node;
	}
	else // if position in grid is not empty, navigate to end of doubly linked list and add at end
	{
		nodeAtGridIndex = nodeGrid[gridIndex];
		while(noteAtGridIndex->next != NULL)
		{
			noteAtGridIndex = noteAtGridIndex->next;
		}
		noteAtGridIndex->next = node;
	}
}

void FixedGraph::removeSceneNode(SceneNode node)
{
	if(node.prev != NULL)
	{
		node.prev->next = node.next;
	}
	else
	{
		nodeGrid = node.next;
	}
	if(node.next != NULL)
	{
		node.next->prev = node.prev;
	}
}

void FixedGraph::updateSceneNode(SceneNode node, int x, int y)
{
	removeSceneNode(node);
	node.xCoordinate = x;
	node.yCoordinate = y;
	addSceneNode(node);
}
