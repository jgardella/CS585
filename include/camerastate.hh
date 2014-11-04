#ifndef _CAMERASTATE_HH_
#define _CAMERASTATE_HH_

#include "worldstate.hh"
#include "asciirenderer.hh"
#include <ncurses.h>

class CameraState : public WorldState
{
	public:
		CameraState(ASCIIRenderer* renderer);

		virtual void tick(float dt);

		virtual void parseInput(int c);
};

#endif
