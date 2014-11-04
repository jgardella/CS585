#include "inputevent.hh"

InputEvent::InputEvent(char inputChar) : IEvent("input")
{
	this->inputChar = inputChar;
}

char InputEvent::getInput()
{
	return inputChar;
}
