#ifndef _DISPATCHER_HH_
#define _DISPATCHER_HH_

#include "itickable.hh"
#include "ilistenercallback.hh"
#include "trie.hh"
#include "queue.hh"
#include "dynamicarray.hh"

// Struct for holding listener modification data (eventType, callback) so it can be stored in one queue.
typedef struct sListenerEvent
{
	IListenerCallback* callback;
	std::string eventType;
	
	sListenerEvent(){ };
	sListenerEvent(std::string type, IListenerCallback* cb) : callback(cb), eventType(type) {}
} tListener;

class Dispatcher : public ITickable
{
	public:
	
		// Constructs a dispatcher.	
		Dispatcher();
		
		// Destructs the dispatcher.
		~Dispatcher();

		// Queues the given listener, associated with the given event type, for addition at the end of this tick.
		// Parameters:
		// string eventType - the type of event that the listener is associated with
		// IListenerCallback* callback - pointer to the listener
		void addListener(std::string eventType, IListenerCallback* callback);
		
		// Queues the given listener, associated with the given event type, for removal at the end of this tick.
		// Parameters:
		// string eventType - the type of event that the listener is associated with
		// IListenerCallback* callback - pointer to the listener to remove
		void removeListener(std::string eventType, IListenerCallback* callback);

		// Queues the given event for dispatch at the end of this tick.
		// Parameters:
		// IEvent* event - the event to dispatch
		void dispatch(IEvent* event);
		
		// Dispatches any events in the event queue, and adds and removes any listeners in their respective queues.
		// Paramters:
		// float dt - change in time
		void tick(float dt);
		
		void setGraph(ISceneGraph* graph);

	private:
		Trie<DynamicArray<IListenerCallback*>*> *callbacks;
		Queue<IEvent*>* eventQueue;
		Queue<sListenerEvent*>* addListenerQueue;
		Queue<sListenerEvent*>* removeListenerQueue;
		
		// Dispatches all of the queued events.	
		void processDeferredEvents();

		// Removes all of the listeners queued for removal.
		void processDeferredListenerRemovals();

		// Adds all of the listeners queued for addition.
		void processDeferredListenerAdditions();

		// Dispatches the given deferred event.
		// Parameters:
		// IEvent* event - the deferred event to dispatch
		void dispatchDeferredEvent(IEvent* event);

		// Adds the given deferred listener, associating it with the given event type.
		// Parameters:
		// string eventType - the type of event that the listener is associated with
		// IListenerCallback* callback - pointer to the deferred listener
		void addDeferredListener(std::string eventType, IListenerCallback* callback);

		// Removes the given deferred listener, which is associated with the given event type.
		// Parameters:
		// string eventType - the type of event that the listener is associated with
		// IListenerCallback* callback - pointer to the deferred listener to remove
		void removeDeferredListener(std::string eventType, IListenerCallback* callback);
};

#endif
