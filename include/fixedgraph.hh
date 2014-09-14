#include "iscenegraph.hh"

class FixedGrid : public ISceneGraph
{
	public:
		FixedGraph(int xDimension, int yDimension);

		void addSceneNode(SceneNode node);
		void removeSceneNode(SceneNode node);
		void updateSceneNode(SceneNode node, int x, int y);
		DynamicArray<SceneNode> getColliders(SceneNode node);
		DynamicArray<SceneNode> getColliders(int x, int y);
		DynamicArray<SceneNode> getColliders(int x, int y, int radius);
		DynamicArray<SceneNode> getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2);

	private:
		SceneNode* nodeGrid[]; // grid of pointers to scene nodes representing scene
		int yDimension;
};
