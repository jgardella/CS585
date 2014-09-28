#include "dispatcher.hh"

void Dispatcher::addListener(std::string eventType, IListenerCallback* callback)
{
	DynamicArray<IListenerCallback*>* callbackArray = *callbacks->get(eventType);
	if(callbackArray == NULL)
	{
		callbackArray = new DynamicArray<IListenerCallback*>();
		callbackArray->pushBack(callback);
		callbacks->add(eventType, callbackArray);
	}
	else
	{
		callbackArray->pushBack(callback);
	}
}

void Dispatcher::removeListener(std::string eventType, IListenerCallback* callback)
{
	unsigned int i;
	DynamicArray<IListenerCallback*>* callbackArray = *callbacks->get(eventType);
	if(callbackArray != NULL)
	{
		for(i = 0; i < callbackArray->length(); i++)
		{
			if(*(callbackArray->get(i)) == callback)
			{
				callbackArray->remove(i);
				break;
			}
		}		
	}
}

void Dispatcher::dispatch(std::string eventType)
{
	unsigned int i;
	DynamicArray<IListenerCallback*>* callbackArray = *callbacks->get(eventType);
	if(callbackArray != NULL)
	{
		for(i = 0; i < callbackArray->length(); i++)
		{
			(*callbackArray->get(i))->execute(*(new IEvent(eventType)));
		}
	}
}
