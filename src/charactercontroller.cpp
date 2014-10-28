#include "charactercontroller.hh"

CharacterController::CharacterController(Character* character, StateMachine* machine)
{
	this->character = character;
	this->machine = machine;
}

void CharacterController::tick(float dt)
{
	machine->tick(dt);
}
