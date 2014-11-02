#ifndef _ATTACKSTATE_HH_
#define _ATTACKSTATE_HH_

#include "istate.hh"
#include "scenemanager.hh"
#include "dynamicarray.hh"
#include "character.hh"
#include "stateevent.hh"
#include <ctime>
#include <cstdlib>

class AttackState : public IState
{
	public:
		AttackState(IActor* actor, Trie<double>* behavior) : IState(actor, behavior) { std::srand(time(NULL)); }

		void tick(float dt);

	private:
		Character* target;
		void scanForTarget();
		void moveTowardTarget();
		void attackTarget();
		unsigned int getAttackDamage();
		bool targetInRange();

};

#endif
