#ifndef _FIXEDGRID_HH_
#define _FIXEDGRID_HH_

#include "iscenegraph.hh"
#include "debug.hh"

// Fixed grid implementation of scene graph.
class FixedGrid : public ISceneGraph
{
	public:
		// Contructs a fixed grid of default size 10x10.
		FixedGrid();
		// Constructs a fixed grid of size xDimension by yDimension.
		FixedGrid(int xDimension, int yDimension);

		// Adds scenenode to grid.
		void addSceneNode(SceneNode *node);
		// Removes scenenode from grid.
		void removeSceneNode(SceneNode *node);
		// Updates position of scenenode to given coordinates.
		void updateSceneNode(SceneNode *node, int x, int y);
		// Gets colliders colliding with given scene node.
		DynamicArray<SceneNode*> *getColliders(SceneNode *node);
		// Gets colliders at given position.
		DynamicArray<SceneNode*> *getColliders(int x, int y);
		// Gets colliders within specified circle.
		DynamicArray<SceneNode*> *getColliders(int x, int y, int radius);
		// Gets colliders within specified rectangle.
		DynamicArray<SceneNode*> *getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2);

	private:
		SceneNode** nodeGrid; // grid of pointers to scene nodes representing scene
		int yDimension, xDimension;
};

#endif
