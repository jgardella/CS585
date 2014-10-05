#include "statemachine.hh"

void StateMachine::tick(float dt)
{
	currentState->tick(dt);
}
