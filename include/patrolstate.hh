#ifndef _PATROLSTATE_HH_
#define _PATROLSTATE_HH_

#include "istate.hh"
#include "scenemanager.hh"
#include "dynamicarray.hh"
#include "character.hh"
#include "stateevent.hh"
#include <ctime>
#include <cstdlib>

class PatrolState : public IState
{
	public:
		PatrolState(IActor* actor, Trie<float>* behavior) : IState(actor, behavior) { }

		void tick(float dt);

};

#endif
