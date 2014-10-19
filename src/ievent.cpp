#include "ievent.hh"
#include "debug.hh"

IEvent::IEvent(std::string type)
{
	DEBUG_LOG("IEVENT", "Constructing IEvent of type " + type + ".");
	eventType = type;
}

std::string IEvent::getType()
{
	return eventType;
}
