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

int main()
{
	#ifndef DEBUG
	Debug::getInstance()->setDebugStatus(false);
	#else
	Debug::getInstance()->setDebugStatus(true);
	Debug::getInstance()->addChannel("LISTENER");
	Debug::getInstance()->addChannel("DISPATCHER");
	Debug::getInstance()->addChannel("TRIE");
	Debug::getInstance()->addChannel("DYNAMICARRAY");
	Debug::getInstance()->unmuteAll();
	#endif
	Listener* listener = new Listener();
	Dispatcher* dispatcher = new Dispatcher();
	dispatcher->addListener("alert", listener);
	dispatcher->dispatch("alert");	
	dispatcher->tick(5);
}
