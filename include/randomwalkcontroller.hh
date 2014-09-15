#ifndef _RANDOMWALKCONTROLLER_HH_
#define _RANDOMWALKCONTROLLER_HH_

#include "iscenegraph.hh"
#include "dynamicarray.hh"
#include "itickable.hh"
#include "actor.hh"
#include <cstdlib>
#include "debug.hh"

class RandomWalkController : public ITickable
{
	public:
		RandomWalkController(DynamicArray<Actor*> *actors, ISceneGraph *graph);
		void tick(float dt);
	private:
		DynamicArray<Actor*> *actors;
		ISceneGraph *graph;
};

#endif
