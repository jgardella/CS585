// Functions for adding and removing listeners.
#include "dispatcher.hh"

void Dispatcher::addListener(std::string eventType, IListenerCallback* callback)
{
	addListenerQueue->enqueue(new tListener(eventType, callback));
}

void Dispatcher::removeListener(std::string eventType, IListenerCallback* callback)
{
	removeListenerQueue->enqueue(new tListener(eventType, callback));	
}

void Dispatcher::dispatch(IEvent* event)
{
	DEBUG_LOG("DISPATCHER", "Dispatching event of type " + event->getType() + "."); 
	// add event to event queue, will be dispatched during tick
	eventQueue->enqueue(event);
}

