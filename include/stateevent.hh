#ifndef _STATEEVENT_HH_
#define _STATEEVENT_HH_

#include <string>
#include "ievent.hh"
#include "debug.hh"

// Event used to switch the state of a state machine.
class StateEvent : public IEvent
{
	public:
		// Constructs a state event with the given state string.
		// Parameters:
		// std::string state - the name of the state
		StateEvent(std::string state);
		std::string getState();
	private:
		std::string stateString;
};

#endif
