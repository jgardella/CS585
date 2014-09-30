#include "dispatcher.hh"

void Dispatcher::addListener(std::string eventType, IListenerCallback* callback)
{
	Debug::getInstance()->log("DISPATCHER", "Adding listener of event type " + eventType + ".");
	DynamicArray<IListenerCallback*>* callbackArray;
	// if specified eventType does not exist in callback trie, create it and add callback
	if(callbacks->get(eventType) == NULL)
	{
		Debug::getInstance()->log("DISPATCHER", "callbackArray is null, creating new array and adding event."); 
		callbackArray = new DynamicArray<IListenerCallback*>();
		callbackArray->pushBack(callback);
		callbacks->add(eventType, callbackArray);
	}
	else // eventType already exists in callback trie, just add callback to array in trie
	{
		Debug::getInstance()->log("DISPATCHER", "callbackArray is not null, adding event."); 
		callbackArray = *callbacks->get(eventType);
		callbackArray->pushBack(callback);
	}
	Debug::getInstance()->log("DISPATCHER", "Event added."); 
}

void Dispatcher::removeListener(std::string eventType, IListenerCallback* callback)
{
	Debug::getInstance()->log("DISPATCHER", "Removing listener of event type " + eventType + ".");
	unsigned int i;
	DynamicArray<IListenerCallback*>* callbackArray;
	// check that events of the given type have previously been added
	if(callbacks->get(eventType) != NULL)
	{
		callbackArray = *callbacks->get(eventType);
		Debug::getInstance()->log("DISPATCHER", "callbackArray is not null, iterating through until listener is found.");
		// iterate through callbacks until correct callback is found
		for(i = 0; i < callbackArray->length(); i++)
		{
			if(*(callbackArray->get(i)) == callback)
			{
				Debug::getInstance()->log("DISPATCHER", "Found listener, removing from array.");
				callbackArray->remove(i);
				break;
			}
		}		
	}
}

void Dispatcher::dispatch(IEvent* event)
{
	Debug::getInstance()->log("DISPATCHER", "Dispatching event of type " + event->getType() + "."); 
	// add event to event queue, will be dispatched during tick
	eventQueue->enqueue(event);
}

void Dispatcher::tick(float dt)
{
	unsigned int i;
	IEvent* event;
	// send all events in event queue to their listeners
	while(!eventQueue->empty())
	{
		event = eventQueue->dequeue();
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
}

Dispatcher::Dispatcher()
{
	Debug::getInstance()->log("DISPATCHER", "Constructing dispatcher.");
	eventQueue = new Queue<IEvent*>();
	callbacks = new Trie<DynamicArray<IListenerCallback*>*>();
}

Dispatcher::~Dispatcher()
{
	delete eventQueue;
	delete callbacks;
}

void Dispatcher::setGraph(ISceneGraph* graph)
{
	
}
