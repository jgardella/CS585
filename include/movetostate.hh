#ifndef _MOVETOSTATE_HH_
#define _MOVETOSTATE_HH_

#include "istate.hh"
#include "scenemanager.hh"
#include "dynamicarray.hh"
#include "character.hh"
#include "stateevent.hh"
#include <ctime>
#include <cstdlib>

class MoveToState : public IState
{
	public:
		MoveToState(IActor* actor) : IState(actor) { }
		void tick(float dt);
		
	private:
		void moveToMoveLocation();

};

#endif
