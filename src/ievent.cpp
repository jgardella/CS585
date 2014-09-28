#include "ievent.hh"

IEvent::IEvent(std::string type)
{
	eventType = type;
}

IEvent::getType()
{
	return eventType;
}
