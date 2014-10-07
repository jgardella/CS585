#include "stateevent.hh"

StateEvent::StateEvent(std::string state) : IEvent("state")
{
	stateString = state;
}

std::string StateEvent::getState()
{
	return stateString;
}
