#ifndef _SCENENODE_HH_
#define _SCENENODE_HH_

// scene node should contain information for collision and position

class SceneNode
{
	public:
		SceneNode(){ };
		SceneNode(int xCoord, int yCoord, int col, SceneNode *p, SceneNode *n):
			xCoordinate(xCoord),
			yCoordinate(yCoord),
			collisionLayer(col),
			prev(p),
			next(n)
		{}
		
		int getX();
		int getY();
		int getCollisionLayer();
		SceneNode* getPrevious();
		SceneNode* getNext();
		void setX(int newX);
		void setY(int newY);
		void setCollisionLayer(int newLayer);
		void setPrevious(SceneNode *newPrev);
		void setNext(SceneNode *newNext);

	private:
		int xCoordinate, yCoordinate, collisionLayer;
		SceneNode *prev; // pointer to previous scene node in same position
		SceneNode *next; // pointer to next scene node in same position
};

#endif
