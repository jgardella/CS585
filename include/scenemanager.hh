#ifndef _SCENEMANAGER_HH_
#define _SCENEMANAGER_HH_

#define NuLL 0

#include "itickable.hh"
#include "scenenode.hh"
#include "dynamicarray.hh"
#include "iscenegraph.hh"

// Singleton class for managing scene.
class SceneManager
{
	public:
		// Gets instance of manager.
		static SceneManager* getInstance();
		// Ticks all tickables.
		void tick(float dt);
		// Adds tickable to list of tickables.
		void addTickable(ITickable *tickable);
		
		// Wrapper functions for SceneManager's scene graph.	
		void addSceneNode(SceneNode *node);
		void removeSceneNode(SceneNode *node);
		void updateSceneNode(SceneNode *node, int x, int y);
		DynamicArray<SceneNode*> *getColliders(SceneNode *node);
		DynamicArray<SceneNode*> *getColliders(int x, int y);
		DynamicArray<SceneNode*> *getColliders(int x, int y, int radius);
		DynamicArray<SceneNode*> *getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2);
	private:
		SceneManager();
		SceneManager(SceneManager const&);
		SceneManager& operator=(SceneManager const&);
		~SceneManager();
		
		static SceneManager *instance;
		DynamicArray<ITickable*> *tickables;
		ISceneGraph *sceneGraph;
};

#endif
