#include "dispatcher.hh"

void Dispatcher::addListener(std::string eventType, IListenerCallback* callback)
{
	Debug::getInstance()->log("DISPATCHER", "Adding listener of event type " + eventType + ".");
	DynamicArray<IListenerCallback*>* callbackArray;
	if(callbacks->get(eventType) == NULL)
	{
		Debug::getInstance()->log("DISPATCHER", "callbackArray is null, creating new array and adding event."); 
		callbackArray = new DynamicArray<IListenerCallback*>();
		callbackArray->pushBack(callback);
		callbacks->add(eventType, callbackArray);
	}
	else
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
	DynamicArray<IListenerCallback*>** callbackArray = callbacks->get(eventType);
	if(callbackArray != NULL)
	{
		Debug::getInstance()->log("DISPATCHER", "callbackArray is not null, iterating through until listener is found.");
		for(i = 0; i < (*callbackArray)->length(); i++)
		{
			if(*((*callbackArray)->get(i)) == callback)
			{
				Debug::getInstance()->log("DISPATCHER", "Found listener, removing from array.");
				(*callbackArray)->remove(i);
				break;
			}
		}		
	}
}

void Dispatcher::dispatch(std::string eventType)
{
	Debug::getInstance()->log("DISPATCHER", "Dispatching event of type " + eventType + "."); 
	eventQueue->enqueue(eventType);
}

void Dispatcher::tick(float dt)
{
	unsigned int i;
	std::string eventType;
	while(!eventQueue->empty())
	{
		eventType = eventQueue->dequeue();
		DynamicArray<IListenerCallback*>** callbackArray = callbacks->get(eventType);
		if(callbackArray != NULL)
		{
			for(i = 0; i < (*callbackArray)->length(); i++)
			{
				(*(*callbackArray)->get(i))->execute(*(new IEvent(eventType)));
			}
		}
	}
}

Dispatcher::Dispatcher()
{
	eventQueue = new Queue<std::string>();
	callbacks = new Trie<DynamicArray<IListenerCallback*>*>();
}

void Dispatcher::setGraph(ISceneGraph* graph)
{
	
}
