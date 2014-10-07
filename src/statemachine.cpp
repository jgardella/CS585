#include "statemachine.hh"

StateMachine::StateMachine(Trie<IState*>* map, Trie<float>* config, std::string startState) : stateMap(map), behavioralConfig(config), currentState(*map->get(startState))
{
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
	currentState = *stateMap->get(stateString);
}
