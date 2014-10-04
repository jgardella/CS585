#ifndef _STATEEVENT_HH_
#define _STATEEVENT_HH_

#include <string>
#include "ievent.hh"

class StateEvent : public IEvent
{
	public:
		StateEvent(std::string state);
		std::string getState();
	private:
		std::string stateString;
};

#endif
