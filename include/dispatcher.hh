#ifndef _DISPATCHER_HH_
#define _DISPATCHER_HH_

#include "itickable.hh"
#include "ilistenercallback.hh"
#include "trie.hh"
#include "queue.hh"
#include "dynamicarray.hh"

class Dispatcher : public ITickable
{
	public:
	
		// Constructs a dispatcher.	
		Dispatcher();
		
		// Destructs the dispatcher.
		~Dispatcher();

		// Adds the given listener, associating it with the given event type.
		// Parameters:
		// string eventType - the type of event that the listener is associated with
		// IListenerCallback* callback - pointer to the listener
		void addListener(std::string eventType, IListenerCallback* callback);

		// Removes the given listener, which is associated with the given event type.
		// Parameters:
		// string eventType - the tyoe of event that the listener is associated with
		// IListenerCallback* callback - pointer to the listener to remove
		void removeListener(std::string eventType, IListenerCallback* callback);

		// Dispatches the given event.
		// Parameters:
		// IEvent* event - the event to dispatch
		void dispatch(IEvent* event);
		
		// Dispatches any events in the event queue to their associated listeners.
		// Paramters:
		// float dt - change in time
		void tick(float dt);
		
		void setGraph(ISceneGraph* graph);

	private:
		Trie<DynamicArray<IListenerCallback*>*> *callbacks;
		Queue<IEvent*>* eventQueue;
};

#endif
