#include "scenenode.hh"

int SceneNode::getX()
{
	return xCoordinate;
}

int SceneNode::getY()
{
	return yCoordinate;
}

SceneNode* SceneNode::getPrevious()
{
	return prev;
}

SceneNode* SceneNode::getNext()
{
	return next;
}

void SceneNode::setX(int newX)
{
	xCoordinate = newX;
}

void SceneNode::setY(int newY)
{
	yCoordinate = newY;
}

void SceneNode::setPrevious(SceneNode *newPrev)
{
	prev = newPrev;
}

void SceneNode::setNext(SceneNode *newNext)
{
	next = newNext;
}

IActor* SceneNode::getActor()
{
	return actor;
}
