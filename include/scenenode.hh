// scene node should contain information for collision and position

class SceneNode
{
	friend class ISceneGraph; // ISceneGraph is friend so it can access scene node's info

	public:
		SceneNode(int xCoord, int yCoord, Collider col, SceneNode *p, SceneNode *n):
			xCoordinate(xCoord),
			yCoordinate(yCoord),
			collider(col),
			prev(p),
			next(n)
		{}

	private:
		int xCoordinate, yCoordinate;
		Collider collider;
		SceneNode *prev; // pointer to previous scene node in same position
		SceneNode *next; // pointer to next scene node in same position
}
