#ifndef _INPUTEVENT_HH_
#define _INPUTEVENT_HH_

#include "ievent.hh"

class InputEvent : public IEvent
{
	public:
		InputEvent(int inputChar);
		int getInput();
	private:
		int inputChar;
};

#endif
