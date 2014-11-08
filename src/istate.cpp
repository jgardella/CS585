// Functions for state interface.
#include "istate.hh"

IState::IState(IActor* act) : actor(act)
{
	DEBUG_LOG("ISTATE", "Constructing IState.");
	dispatcher = new Dispatcher();
	active = false;
}

void IState::addListener(std::string type, IListenerCallback* listener)
{
	DEBUG_LOG("ISTATE", "Adding listener of type " + type + " to IState.");
	dispatcher->addListener(type, listener);
}

void IState::setActor(IActor* actor)
{
	this->actor = actor;
}

void IState::preStateStart()
{
	active = true;
}
