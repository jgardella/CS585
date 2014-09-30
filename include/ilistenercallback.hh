#ifndef _ILISTENERCALLBACK_HH_
#define _ILISTENERCALLBACK_HH_

#include "ievent.hh"

class IListenerCallback
{
	public:
		virtual void execute(IEvent event) = 0;
};

#endif
