#include "ievent.hh"

IEvent::IEvent(std::string type)
{
	eventType = type;
}

std::string IEvent::getType()
{
	return eventType;
}
