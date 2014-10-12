// Tick function and related functions for processedig deferrments.
#include "dispatcher.hh"

void Dispatcher::tick(float dt)
{
	processDeferredListenerAdditions();
	processDeferredEvents();
	processDeferredListenerRemovals();
}

void Dispatcher::processDeferredEvents()
{
	while(!eventQueue->empty())
	{
		dispatchDeferredEvent(eventQueue->dequeue());
	}
}

void Dispatcher::processDeferredListenerRemovals()
{
	while(!removeListenerQueue->empty())
	{
		tListener* listener = removeListenerQueue->dequeue();
		removeDeferredListener(listener->eventType, listener->callback);
	}
}

void Dispatcher::processDeferredListenerAdditions()
{
	while(!addListenerQueue->empty())
	{
		tListener* listener = addListenerQueue->dequeue();
		addDeferredListener(listener->eventType, listener->callback);
	}
}

void Dispatcher::dispatchDeferredEvent(IEvent* event)
{
	unsigned int i;
	DynamicArray<IListenerCallback*>* callbackArray;
	if(callbacks->get(event->getType()) != NULL)
	{
		callbackArray = *callbacks->get(event->getType());
		// iterate through callbacks of given event type and execute them with the event
		for(i = 0; i < callbackArray->length(); i++)
		{
			(*callbackArray->get(i))->execute(event);
		}
	}
}

void Dispatcher::addDeferredListener(std::string eventType, IListenerCallback* callback)
{
	DEBUG_LOG("DISPATCHER", "Adding listener of event type " + eventType + ".");
	DynamicArray<IListenerCallback*>* callbackArray;
	// if specified eventType does not exist in callback trie, create it and add callback
	if(callbacks->get(eventType) == NULL)
	{
		DEBUG_LOG("DISPATCHER", "callbackArray is null, creating new array and adding event."); 
		callbackArray = new DynamicArray<IListenerCallback*>();
		callbackArray->pushBack(callback);
		callbacks->add(eventType, callbackArray);
	}
	else // eventType already exists in callback trie, just add callback to array in trie
	{
		DEBUG_LOG("DISPATCHER", "callbackArray is not null, adding event."); 
		callbackArray = *callbacks->get(eventType);
		callbackArray->pushBack(callback);
	}
	DEBUG_LOG("DISPATCHER", "Event added."); 
}

void Dispatcher::removeDeferredListener(std::string eventType, IListenerCallback* callback)
{
	DEBUG_LOG("DISPATCHER", "Removing listener of event type " + eventType + ".");
	unsigned int i;
	DynamicArray<IListenerCallback*>* callbackArray;
	// check that events of the given type have previously been added
	if(callbacks->get(eventType) != NULL)
	{
		callbackArray = *callbacks->get(eventType);
		DEBUG_LOG("DISPATCHER", "callbackArray is not null, iterating through until listener is found.");
		// iterate through callbacks until correct callback is found
		for(i = 0; i < callbackArray->length(); i++)
		{
			if(*(callbackArray->get(i)) == callback)
			{
				DEBUG_LOG("DISPATCHER", "Found listener, removing from array.");
				callbackArray->remove(i);
				break;
			}
		}		
	}
}
