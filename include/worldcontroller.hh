#ifndef _WORLDCONTROLLER_HH_
#define _WORLDCONTROLLER_HH_

#include "asciirenderer.hh"
#include "camerastate.hh"
#include "selectstate.hh"
#include "inspectstate.hh"

class WorldController
{
	public:
		WorldController(ASCIIRenderer* renderer);
		
		void tick(float dt);
	private:
		ASCIIRenderer* renderer;
		StateMachine* machine;
};

#endif
