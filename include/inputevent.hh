#ifndef _INPUTEVENT_HH_
#define _INPUTEVENT_HH_

#include "ievent.hh"

class InputEvent : public IEvent
{
	public:
		InputEvent(char inputChar);
		char getInput();
	private:
		char inputChar;
};

#endif
