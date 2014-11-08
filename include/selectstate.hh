#ifndef _SELECTSTATE_HH_
#define _SELECTSTATE_HH_

#include "worldstate.hh"

class SelectState : public WorldState
{
	public:
		SelectState(ASCIIRenderer* renderer);		

		virtual void tick(float dt);

		virtual void parseInput(int c, bool keyDown);
};

#endif
