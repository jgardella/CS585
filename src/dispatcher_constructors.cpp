// Constructors for Dispatcher.
#include "dispatcher.hh"

Dispatcher::Dispatcher()
{
	DEBUG_LOG("DISPATCHER", "Constructing dispatcher.");
	eventQueue = new Queue<IEvent*>();
	addListenerQueue = new Queue<tListener*>();
	removeListenerQueue = new Queue<tListener*>();
	callbacks = new Trie<DynamicArray<IListenerCallback*>*>();
}

Dispatcher::~Dispatcher()
{
	delete eventQueue;
	delete addListenerQueue;
	delete removeListenerQueue;
	delete callbacks;
}
