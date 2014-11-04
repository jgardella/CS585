#include "inputevent.hh"

InputEvent::InputEvent(int inputChar) : IEvent("input")
{
	this->inputChar = inputChar;
}

int InputEvent::getInput()
{
	return inputChar;
}
