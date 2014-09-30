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
		
		Dispatcher();
		
		~Dispatcher();

		void addListener(std::string eventType, IListenerCallback* callback);

		void removeListener(std::string eventType, IListenerCallback* callback);

		void dispatch(IEvent* event);
		
		void tick(float dt);
		
		void setGraph(ISceneGraph* graph);

	private:
		Trie<DynamicArray<IListenerCallback*>*> *callbacks;
		Queue<IEvent*>* eventQueue;
};

#endif
