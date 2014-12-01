#ifndef _ATTACKSTATE_HH_
#define _ATTACKSTATE_HH_

#include "istate.hh"
#include "scenemanager.hh"
#include "dynamicarray.hh"
#include "character.hh"
#include "stateevent.hh"
#include "ilistenercallback.hh"
#include "deathevent.hh"
#include "ievent.hh"
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
		void nullifyTarget();


		// Listener callback for deaths
		class OnDeathEvent : public IListenerCallback
		{
			public:
				OnDeathEvent() { }
				void setInstance(AttackState* state)
				{
					this->state = state;
				}
				
				// Transfers gold and removes the controller for the dead actor.		
				virtual void execute(IEvent* event)
				{
					DEBUG_LOG("LEVEL", "Death event callback executed.");
					if(event->getType().compare("death") == 0)
					{
						state->nullifyTarget();
					}
				}
				

			private:
				AttackState* state;
		} onDeathEvent; 
};

#endif
