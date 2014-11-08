#ifndef _INSPECTSTATE_HH_
#define _INSPECTSTATE_HH_

#include "worldstate.hh"
#include "asciirenderer.hh"

class InspectState : public WorldState
{
	public:
		InspectState(ASCIIRenderer* renderer);

		virtual void tick(float dt);

		virtual void parseInput(int c, bool keyDown);

};

#endif
