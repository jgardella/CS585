#include "worldstate.hh"

WorldState::WorldState(ASCIIRenderer* renderer) : IState(NULL)
{
	DEBUG_LOG("WORLDSTATE", "Constructing new world state.");
	this->renderer = renderer;
	inputListener.setController(this);
}
