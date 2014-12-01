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
		AttackState(Character* character);

		void tick(float dt);

	private:
		Character* character;

		void scanForTarget();
		void moveTowardTarget();
		void attackTarget();
		unsigned int getAttackDamage();
		bool targetInRange();

};

#endif
