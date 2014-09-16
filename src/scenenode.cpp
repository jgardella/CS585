#include "scenenode.hh"

SceneNode::~SceneNode()
{

}

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

int SceneNode::isCollider()
{
	return isNodeCollider;
}

void SceneNode::setPrevious(SceneNode *newPrev)
{
	prev = newPrev;
}

void SceneNode::setNext(SceneNode *newNext)
{
	next = newNext;
}

void SceneNode::setCollider(bool newVal)
{
	isNodeCollider = newVal;
}

void SceneNode::deleteNode()
{
	toBeDeleted = true;
}

bool SceneNode::isReadyForDeletion()
{
	return toBeDeleted;
}
