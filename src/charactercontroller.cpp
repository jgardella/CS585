#include "charactercontroller.hh"

CharacterController::CharacterController(Character* character, StateMachine* machine, unsigned int id)
{
	this->character = character;
	this->machine = machine;
	this->id = id;
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
	machine->updateState("moveto");
}

unsigned int CharacterController::getID()
{
	return id;
}
