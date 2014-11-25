#ifndef _SLEEPSTATE_HH_
#define _SLEEPSTATE_HH_

#include "istate.hh"
#include "character.hh"
#include "building.hh"
#include "iactor.hh"
#include "levelmanager.hh"

class SleepState : public IState
{
	public:
		SleepState(IActor* actor);
		void tick(float dt);
	
	private:
		Building* home;
		bool isSleeping;
};

#endif
