#ifndef _RANDOMWALKCONTROLLER_HH_
#define _RANDOMWALKCONTROLLER_HH_

#include "iscenegraph.hh"
#include "dynamicarray.hh"
#include "itickable.hh"
#include "actor.hh"
#include <cstdlib>
#include "debug.hh"

// Random walk controller which moves actors and deals with collisions.
class RandomWalkController : public ITickable
{
	public:
		// Constructs controller with given array of actors.
		RandomWalkController(DynamicArray<Actor*> *actors);
		// Ticks actors.
		void tick(float dt);
		void setGraph(ISceneGraph*);
	private:
		DynamicArray<Actor*> *actors;
		ISceneGraph *graph;
		float timeCounter;
};

#endif
