#ifndef _ISCENEGRAPH_HH_
#define _ISCENEGRAPH_HH_

#include "scenenode.hh"
#include "dynamicarray.hh"

// Interface for implementing a scene.
class ISceneGraph
{
	public:
		// Add the given scene node to the graph.
		// Parameters:
		// SceneNode* node - pointer to the node to add
		virtual void addSceneNode(SceneNode* node) = 0;

		// Remove the given scene node from the graph.
		// Parameters:
		// SceneNode* node - pointer to the node to remove
		virtual void removeSceneNode(SceneNode* node) = 0;

		// Updates the position of the given scenenode.
		// Parameters:
		// SceneNode* node - pointer to the node to update
		// int x - new x coordinate for the node
		// int y - new y coordinate for the node
		virtual void updateSceneNode(SceneNode* node, int x, int y) = 0;

		// Finds all scene nodes colliding with the given scene node.
		// Parameters:
		// SceneNode* node - the node to check for collisions against
		virtual DynamicArray<SceneNode*> *getColliders(SceneNode* node) = 0;

		// Finds all collidable scene nodes at the given coordinate.
		// Parameters:
		// int x - x coordinate
		// int y - y coordinate
		// bool ignoreNonCollisionLayer - whether or not to ignore the non-collision layer (0)
		virtual DynamicArray<SceneNode*> *getColliders(int x, int y, bool ignoreNonCollisionLayer) = 0;

		// Finds all collidable scene nodes within the given circle.
		// Parameters:
		// int x - x coordinate of circle center
		// int y - y coordinate of circle center
		// int radius - radius of circle
		virtual DynamicArray<SceneNode*> *getColliders(int x, int y, int radius) = 0;

		// Finds all collidable scene nodes within the given rectangle.
		// Parameters:
		// int cornerX1 - x coordinate of first corner
		// int cornerY1 - y coordinate of first corner
		// int cornerX2 - x coordinate of second corner
		// int cornerY2 - y coordinate of second corner
		virtual DynamicArray<SceneNode*> *getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2) = 0;
};

#endif
