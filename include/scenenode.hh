#ifndef _SCENENODE_HH_
#define _SCENENODE_HH_

// scene node should contain information for collision and position

class SceneNode
{
	public:
		SceneNode(){ };
		~SceneNode();
		SceneNode(int xCoord, int yCoord, bool col, SceneNode *p, SceneNode *n):
			xCoordinate(xCoord),
			yCoordinate(yCoord),
			isNodeCollider(col),
			prev(p),
			next(n)
		{toBeDeleted = false;}
		
		int getX();
		int getY();
		int isCollider();
		SceneNode* getPrevious();
		SceneNode* getNext();
		void setX(int newX);
		void setY(int newY);
		void setCollider(bool newVal);
		void setPrevious(SceneNode *newPrev);
		void setNext(SceneNode *newNext);
		void deleteNode();
		bool isReadyForDeletion();
	private:
		int xCoordinate, yCoordinate;
		bool isNodeCollider, toBeDeleted;
		SceneNode *prev; // pointer to previous scene node in same position
		SceneNode *next; // pointer to next scene node in same position
};

#endif
