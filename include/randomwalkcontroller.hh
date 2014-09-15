#include "dynamicarray.hh"
#include "itickable.hh"
#include "actor.hh"

class RandomWalkController : public ITickable
{
	public:
		RandomWalkController(DynamicArray<Actor> *actors);
		void tick(float dt);
	private:
		DynamicArray<Actor*> *actors;
};
