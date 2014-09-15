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
		static SceneManager* getInstance();
		void tick(float dt);
		void addTickable(ITickable *tickable);
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
