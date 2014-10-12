#ifndef _SCENEMANAGER_HH_
#define _SCENEMANAGER_HH_

#define NuLL 0

#include "itickable.hh"
#include "scenenode.hh"
#include "dynamicarray.hh"
#include "iscenegraph.hh"
#include "fixedgrid.hh"
#include "debug.hh"

// Singleton class for managing scene.
class SceneManager
{
	public:
		// Gets instance of manager.
		static SceneManager* getInstance();
		
		// Ticks all tickables in the scenemanager's tickable list.
		// Parameters:
		// float dt - the change in time since the last tick
		void tick(float dt);

		// Adds the given tickable to the scenemanager's of tickables.
		// Parameters:
		// ITickable* tickable - the a pointer to the tickable to be added
		void addTickable(ITickable* tickable);
		
		// Sets the scenemanager's scene graph to the given graph.
		// Paramters:
		// ISceneGraph* graph - pointer to a scene graph
		void setGraph(ISceneGraph* graph);
	
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
		
		static SceneManager* instance;
		DynamicArray<ITickable*>* tickables;
		ISceneGraph* sceneGraph;
};

#endif
