#include "dispatcher.hh"
#include "debug.hh"
#include "jtest.hh"

class SetEvent : public IEvent
{
	public:
		SetEvent(std::string type, int value);		
		int getValue();
	private:
		int value;
};

SetEvent::SetEvent(std::string type, int value) : IEvent(type)
{
	this->value = value;	
}

int SetEvent::getValue()
{
	return value;
}

class Listener : public IListenerCallback
{
	public:
		Listener(int value);
		void execute(IEvent* event);
		int getValue();
	private:
		int value;
};

Listener::Listener(int value)
{
	this->value = value;
}

int Listener::getValue()
{
	return value;
}

void Listener::execute(IEvent* event)
{
	Debug::getInstance()->log("LISTENER", "Listener callback executed with event of type " + event->getType() + ".");
	if(event->getType().compare("set") == 0)
	{
		Debug::getInstance()->log("LISTENER", "Setting listener's value.");
		value = ((SetEvent*)event)->getValue();
	}
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
	Listener* listener = new Listener(3);
	Dispatcher* dispatcher = new Dispatcher();
	SetEvent* event = new SetEvent("set", 5);
	SetEvent* nonExistentEvent = new SetEvent("run", 3);
	// add listener to dispatcher
	dispatcher->addListener("set", listener);
	// dispatch event
	dispatcher->dispatch(event);	
	// simulate tick
	dispatcher->tick(5); 
	JTest<int>::testEquality("Event succesfully set value in listener", 5, listener->getValue());
	// dispatch event with no associated listeners
	dispatcher->dispatch(nonExistentEvent);
	// simulate tick
	dispatcher->tick(5);
	JTest<int>::testEquality("Incorrect type event did not change value of listener", 5, listener->getValue());
	// remove listener
	dispatcher->removeListener("set", listener);
	// dispatch event
	dispatcher->dispatch(event);
	// simulate tick
	dispatcher->tick(5);
	JTest<int>::testEquality("Value of listener not modified after it is removed from dispatcher.", 5, listener->getValue());
}
