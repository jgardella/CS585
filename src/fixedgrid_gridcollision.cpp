#include "fixedgrid.hh"

DynamicArray<SceneNode*> FixedGrid::getColliders(SceneNode node)
{
	DynamicArray<SceneNode*> *colliders = new DynamicArray<SceneNode*>();
	SceneNode *otherNode;
	if(node.isCollider()) // if node is on non-collision layer, return empty array
	{
		otherNode = nodeGrid[node.getX() + node.getY() * yDimension];
		while(otherNode != NULL)
		{
			if(otherNode->isCollider())
			{
				colliders->pushBack(otherNode);
			}
			otherNode = otherNode->getNext();
		}
	}
	return *colliders;
}

DynamicArray<SceneNode*> FixedGrid::getColliders(int x, int y)
{
	DynamicArray<SceneNode*> *colliders = new DynamicArray<SceneNode*>();
	SceneNode *node = nodeGrid[x + y * yDimension];
	while(node != NULL)
	{
		colliders->pushBack(node);
	}
	return *colliders;
}

DynamicArray<SceneNode*> FixedGrid::getColliders(int x, int y, int radius)
{
	DynamicArray<SceneNode*> *colliders = new DynamicArray<SceneNode*>();
	// TODO: implement circular collider scan
	return *colliders;

}

DynamicArray<SceneNode*> FixedGrid::getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2)
{
	int i, j;
	DynamicArray<SceneNode*> *colliders = new DynamicArray<SceneNode*>();
	for(i = cornerX1; i <= cornerX2; i++)
	{
		for(j = cornerY1; j <= cornerY2; j++)
		{
			SceneNode *node = nodeGrid[i + j * yDimension];
			while(node != NULL)
			{
				colliders->pushBack(node);
			}	
		}
	}
	return *colliders;
}
