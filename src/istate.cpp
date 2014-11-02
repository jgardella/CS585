// Functions for state interface.
#include "istate.hh"

IState::IState(IActor* act, Trie<double>* config) : actor(act), behavioralConfig(config) 
{
	DEBUG_LOG("ISTATE", "Constructing IState.");
	dispatcher = new Dispatcher();
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

void IState::setConfig(Trie<double>* config)
{
	behavioralConfig = config;
}
