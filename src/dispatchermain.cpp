#include "dispatcher.hh"
#include "debug.hh"

class Listener : public IListenerCallback
{
	public:
		void execute(IEvent event);
};

void Listener::execute(IEvent event)
{
	Debug::getInstance()->log("LISTENER", "Listener callback executed with event of type " + event.getType() + ".");
}

class Event : public IEvent
{
	public:
		Event(std::string type);		
};

Event::Event(std::string type) : IEvent(type)
{
}

void debugInit()
{
	#ifndef DEBUG
	Debug::getInstance()->setDebugStatus(false);
	#else
	Debug::getInstance()->setDebugStatus(true);
	Debug::getInstance()->addChannel("LISTENER");
	Debug::getInstance()->addChannel("DISPATCHER");
	Debug::getInstance()->unmuteAll();
	#endif
}

int main()
{
	debugInit();
	// instantiate listener and dispatcher
	Listener* listener = new Listener();
	Dispatcher* dispatcher = new Dispatcher();
	Event* event = new Event("alert");
	Event* nonExistentEvent = new Event("run");
	// add listener to dispatcher
	dispatcher->addListener("alert", listener);
	// dispatch event
	dispatcher->dispatch(event);	
	// simulate tick
	dispatcher->tick(5); // expected: listener runs execute, printing out its debug statement
	// dispatch event with no associated listeners
	dispatcher->dispatch(nonExistentEvent);
	// simulate tick
	dispatcher->tick(5); // expected: no listener of type run, nothing printed
	// remove listener
	dispatcher->removeListener("alert", listener);
	// dispatch event
	dispatcher->dispatch(event);
	// simulate tick
	dispatcher->tick(5); // expected: no listener of type alert, nothing printed
}
