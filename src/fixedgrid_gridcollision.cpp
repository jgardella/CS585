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
	DEBUG_LOG("FIXEDGRID", "Getting colliders at position (" + std::to_string(x) + ", " + std::to_string(y) + ").");
	DynamicArray<SceneNode*> *colliders = new DynamicArray<SceneNode*>();
	if(x >= 0 && y >= 0 && x < xDimension && y < yDimension)
	{
		SceneNode* node = nodeGrid[x + y * yDimension];
		while(node != NULL)
		{
			if(node->getActor()->getCollisionLayer() > 0) // if node is not on non-collision layer, add to array
			{
				colliders->pushBack(node);
			}
		}
	}
	return colliders;
}

DynamicArray<SceneNode*> *FixedGrid::getColliders(int x, int y, int radius)
{
	int l, r, j;
	DEBUG_LOG("FIXEDGRID", "Getting colliders within circle of center (" + std::to_string(x) + ", " + std::to_string(y) + ") and of radius " + std::to_string(radius) + ".");
	DynamicArray<SceneNode*> *colliders = new DynamicArray<SceneNode*>();
	SceneNode* node;
	if(x - radius >= 0 && y - radius >= 0 && x + radius < xDimension && y + radius < yDimension)
	{
		for(l = 0, r = radius - 1; l < radius; l++, r--)
		{
			for(j = y - l; j < 2 * l + 1; j++)
			{
				node = nodeGrid[x - radius + 1 + l + j * yDimension];
				while(node != NULL)
				{
					if(node->getActor()->getCollisionLayer() > 0)
					{
						colliders->pushBack(node);
					}
				}	
				node = nodeGrid[x + r + j * yDimension];
				while(node != NULL)
				{
					if(node->getActor()->getCollisionLayer() > 0)
					{
						colliders->pushBack(node);
					}
				}		
			}
		}
	}
	return colliders;

}

DynamicArray<SceneNode*> *FixedGrid::getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2)
{
	int i, j;
	DEBUG_LOG("FIXEDGRID", "Getting colliders within rectangle of corners (" + std::to_string(cornerX1) + ", " + std::to_string(cornerY1) + ") and (" + std::to_string(cornerX2) + ", " + std::to_string(cornerY2) + ".");
	DynamicArray<SceneNode*> *colliders = new DynamicArray<SceneNode*>();
	SceneNode* node;
	if(cornerX1 >= 0 && cornerX2 >= 0 && cornerY1 >= 0 && cornerY2 >= 0 && cornerX1 < xDimension && cornerX2 < xDimension && cornerY1 < yDimension && cornerY2 < yDimension)
	{
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
	}
	return colliders;
}
