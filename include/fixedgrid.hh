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
		// Parameters:
		// int xDimension - the x dimension of the grid
		// int yDimension - the y dimension of the grid
		FixedGrid(int xDimension, int yDimension);

		// Add the given scene node to the grid.
		// Parameters:
		// SceneNode* node - pointer to the node to add
		void addSceneNode(SceneNode *node);

		// Remove the given scene node from the grid.
		// Parameters:
		// SceneNode* node - pointer to the node to remove
		void removeSceneNode(SceneNode *node);
		
		// Updates the position of the given scenenode.
		// Parameters:
		// SceneNode* node - pointer to the node to update
		// int x - new x coordinate for the node
		// int y - new y coordinate for the node
		void updateSceneNode(SceneNode *node, int x, int y);
		
		// Finds all scene nodes colliding with the given scene node.
		// Parameters:
		// SceneNode* node - the node to check for collisions against
		DynamicArray<SceneNode*> *getColliders(SceneNode *node);
		
		// Finds all collidable scene nodes at the given coordinate.
		// Parameters:
		// int x - x coordinate
		// int y - y coordinate
		DynamicArray<SceneNode*> *getColliders(int x, int y);
		
		// Finds all collidable scene nodes within the given circle.
		// Parameters:
		// int x - x coordinate of circle center
		// int y - y coordinate of circle center
		// int radius - radius of circle
		DynamicArray<SceneNode*> *getColliders(int x, int y, int radius);
		
		// Finds all collidable scene nodes within the given rectangle.
		// Parameters:
		// int cornerX1 - x coordinate of first corner
		// int cornerY1 - y coordinate of first corner
		// int cornerX2 - x coordinate of second corner
		// int cornerY2 - y coordinate of second corner
		DynamicArray<SceneNode*> *getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2);

	private:
		SceneNode** nodeGrid; // grid of pointers to scene nodes representing scene
		int yDimension, xDimension;
};

#endif
