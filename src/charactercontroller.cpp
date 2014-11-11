#include "charactercontroller.hh"

CharacterController::CharacterController(Character* character, StateMachine* machine)
{
	this->character = character;
	this->machine = machine;
	timeCounter = 0;
}

void CharacterController::tick(float dt)
{
	timeCounter += dt;
	if(timeCounter >= 1)
	{	
		machine->tick(dt);
		timeCounter = 0;
	}
}

void CharacterController::issueMoveCommand(unsigned int x, unsigned int y)
{
	character->setMoveLocation(x, y);
}
