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
		// Adds scenenode to manager's graph.
		void addSceneNode(SceneNode node);
	private:
		SceneManager();
		SceneManager(SceneManager const&);
		SceneManager& operator=(SceneManager const&);
		~SceneManager();
		
		static SceneManager *instance;
		DynamicArray<ITickable*> *tickables;
		DynamicArray<SceneNode> *sceneNodes;
		ISceneGraph *sceneGraph;
};

#endif
