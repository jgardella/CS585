#include "scenenode.hh"

// Interface for implementing a scene.
class ISceneGraph
{
	public:
		virtual void addSceneNode(SceneNode node) = 0;
		virtual void removeSceneNode(SceneNode node) = 0;
		virtual void updateSceneNode(SceneNode node, int x, int y) = 0;
		virtual DynamicArray<SceneNode> getColliders(SceneNode node) = 0;
		virtual DynamicArray<SceneNode> getColliders(int x, int y) = 0;
		virtual DynamicArray<SceneNode> getColliders(int x, int y, int radius) = 0;
		virtual DynamicArray<SceneNode> getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2) = 0;
}
