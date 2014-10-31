#ifndef _CHARACTERCONTROLLER_HH_
#define _CHARACTERCONTROLLER_HH_

#include "character.hh"
#include "itickable.hh"
#include "trie.hh"
#include "istate.hh"
#include "statemachine.hh"

class CharacterController : public ITickable
{
	public:
		CharacterController(Character* character, StateMachine* machine);
	
		void tick(float dt);

	private:
		Character* character;
		StateMachine* machine;
		float timeCounter;
};

#endif
