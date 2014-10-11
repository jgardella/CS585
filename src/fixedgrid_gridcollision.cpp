// Functions for retrieving colliders in fixed grid.
#include "fixedgrid.hh"

DynamicArray<SceneNode*> *FixedGrid::getColliders(SceneNode *node)
{
	DEBUG_LOG("FIXEDGRID", "Getting colliders based on scene node.");
	DynamicArray<SceneNode*>* colliders = new DynamicArray<SceneNode*>();
	IActor* actor = node->getActor();
	IActor* otherActor;
	SceneNode *otherNode;
	if(actor->getCollisionLayer() > 0) // if node is on non-collision layer, return empty array
	{
		otherNode = nodeGrid[node->getX() + node->getY() * yDimension];
		while(otherNode != NULL)
		{
			otherActor = otherNode->getActor();
			if(actor->getCollisionLayer() == otherActor->getCollisionLayer()) // if node's actors are on same collision layer, add to array
			{
				colliders->pushBack(otherNode);
			}
			otherNode = otherNode->getNext();
		}
	}
	return colliders;
}

DynamicArray<SceneNode*> *FixedGrid::getColliders(int x, int y)
{
	DEBUG_LOG("FIXEDGRID", "Getting colliders based on position.");
	DynamicArray<SceneNode*> *colliders = new DynamicArray<SceneNode*>();
	SceneNode* node = nodeGrid[x + y * yDimension];
	while(node != NULL)
	{
		if(node->getActor()->getCollisionLayer() > 0) // if node is not on non-collision layer, add to array
		{
			colliders->pushBack(node);
		}
	}
	return colliders;
}

DynamicArray<SceneNode*> *FixedGrid::getColliders(int x, int y, int radius)
{
	DEBUG_LOG("FIXEDGRID", "Getting colliders based on circle.");
	DynamicArray<SceneNode*> *colliders = new DynamicArray<SceneNode*>();
	// TODO: implement circular collider scan
	return colliders;

}

DynamicArray<SceneNode*> *FixedGrid::getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2)
{
	int i, j;
	DEBUG_LOG("FIXEDGRID", "Getting colliders based on rectangle.");
	DynamicArray<SceneNode*> *colliders = new DynamicArray<SceneNode*>();
	SceneNode* node;
	for(i = cornerX1; i <= cornerX2; i++)
	{
		for(j = cornerY1; j <= cornerY2; j++)
		{
			node = nodeGrid[i + j * yDimension];
			while(node != NULL)
			{
				if(node->getActor()->getCollisionLayer() > 0) // if node is not on non-collision layer, add to array
				{
					colliders->pushBack(node);
				}
			}	
		}
	}
	return colliders;
}
