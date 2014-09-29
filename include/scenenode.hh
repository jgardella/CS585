#ifndef _SCENENODE_HH_
#define _SCENENODE_HH_

#include "iactor.hh"

// Scene node class.
class SceneNode
{
	public:
		SceneNode(){ };
		SceneNode(int xCoord, int yCoord, SceneNode *p, SceneNode *n):
			xCoordinate(xCoord),
			yCoordinate(yCoord),
			prev(p),
			next(n)
		{}
		
		int getX();
		int getY();
		SceneNode* getPrevious();
		SceneNode* getNext();
		void setX(int newX);
		void setY(int newY);
		void setPrevious(SceneNode* newPrev);
		void setNext(SceneNode* newNext);
		IActor* getActor();
	private:
		int xCoordinate, yCoordinate;
		SceneNode* prev; // pointer to previous scene node in same position
		SceneNode* next; // pointer to next scene node in same position
		IActor* actor;
};

#endif
