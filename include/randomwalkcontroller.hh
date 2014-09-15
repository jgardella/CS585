#ifndef _RANDOMWALKCONTROLLER_HH_
#define _RANDOMWALKCONTROLLER_HH_

#include "dynamicarray.hh"
#include "itickable.hh"
#include "actor.hh"
#include <cstdlib>

class RandomWalkController : public ITickable
{
	public:
		RandomWalkController(DynamicArray<Actor*> *actors);
		void tick(float dt);
	private:
		DynamicArray<Actor*> *actors;
};

#endif
