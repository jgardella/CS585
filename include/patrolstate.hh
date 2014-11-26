#ifndef _PATROLSTATE_HH_
#define _PATROLSTATE_HH_

#include "istate.hh"
#include "scenemanager.hh"
#include "levelmanager.hh"
#include "dynamicarray.hh"
#include "character.hh"
#include "stateevent.hh"
#include <ctime>
#include <cstdlib>

class PatrolState : public IState
{
	public:
		PatrolState(IActor* actor) : IState(actor) { }
		void tick(float dt);

};

#endif
