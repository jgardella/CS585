// Functions for state interface.
#include "istate.hh"

void IState::addListener(std::string type, IListenerCallback* listener)
{
	dispatcher->addListener(type, listener);
}

IState::IState(IActor* act, Trie<float>* config) : actor(act), behavioralConfig(config) 
{
	dispatcher = new Dispatcher();
}
