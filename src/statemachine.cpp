#include "statemachine.hh"

StateMachine::StateMachine(Trie<IState*>* map, Trie<double>* config, std::string startState) : stateMap(map), behavioralConfig(config), currentState(*map->get(startState))
{
	DEBUG_LOG("STATEMACHINE", "Constructing StateMachine with start state: " + startState + ".");
	onStateTransition.setInstance(this);
}

void StateMachine::tick(float dt)
{
	currentState->tick(dt);
}


IListenerCallback* StateMachine::getListener()
{
	return &onStateTransition;
}

void StateMachine::updateState(std::string stateString)
{
	DEBUG_LOG("STATEMACHINE", "Updating state to: " + stateString + ".");
	currentState = *stateMap->get(stateString);
}
