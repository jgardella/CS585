#ifndef _STATEEVENT_HH_
#define _STATEEVENT_HH_

#include <string>
#include "ievent.hh"

// Event used to switch the state of a state machine.
class StateEvent : public IEvent
{
	public:
		StateEvent(std::string state);
		std::string getState();
	private:
		std::string stateString;
};

#endif
