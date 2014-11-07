#include "inputevent.hh"

InputEvent::InputEvent(int inputChar, bool keyDown) : IEvent("input")
{
	this->inputChar = inputChar;
	this->keyDown = keyDown;
}

int InputEvent::getInput()
{
	return inputChar;
}

bool InputEvent::getKeyDown()
{
	return keyDown;
}
