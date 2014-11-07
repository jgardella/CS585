#ifndef _INPUTEVENT_HH_
#define _INPUTEVENT_HH_

#include "ievent.hh"

class InputEvent : public IEvent
{
	public:
		InputEvent(int inputChar, bool down);
		int getInput();
		bool getKeyDown();
	private:
		int inputChar;
		bool keyDown;
};

#endif
