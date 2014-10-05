#ifndef _ISTATE_HH_
#define _ISTATE_HH_

#include "itickable.hh"
#include "iactor.hh"

class IState : public ITickable
{
	protected:
		IState(IActor* act) : actor(act) {}
		IActor* actor;
};

#endif
