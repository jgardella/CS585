#include "stateevent.hh"

StateEvent::StateEvent(std::string state) : IEvent("state")
{
	DEBUG_LOG("STATEEVENT", "Constructing StateEvent with state: " + state + ".");
	stateString = state;
}

std::string StateEvent::getState()
{
	return stateString;
}
