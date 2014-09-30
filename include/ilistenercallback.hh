#ifndef _ILISTENERCALLBACK_HH_
#define _ILISTENERCALLBACK_HH_

#include "ievent.hh"

// Interface for listener callbacks.
class IListenerCallback
{
	public:
		// Virtual method which serves as the callback function for the listener. This function dictates what the listener does when it recieves an event.
		// Parameters:
		// IEvent event - the event the listener recieved
		virtual void execute(IEvent* event) = 0;
};

#endif
