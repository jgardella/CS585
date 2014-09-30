#ifndef _IEVENT_HH_
#define _IEVENT_HH_

#include <string>

// Interface for events.
class IEvent
{
	public:
		

		virtual std::string getType();
	
	protected:
		IEvent(std::string type);
		std::string eventType;
};

#endif
