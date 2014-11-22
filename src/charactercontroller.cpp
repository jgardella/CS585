#include "charactercontroller.hh"

CharacterController::CharacterController(Character* character, StateMachine* machine, unsigned int id)
{
	onActorEvent.setInstance(this);
	this->character = character;
	character->addListener("state", &onActorEvent);
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

unsigned int CharacterController::getID()
{
	return id;
}

void CharacterController::updateState(std::string state)
{
	machine->updateState(state);
}
