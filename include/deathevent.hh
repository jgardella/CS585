#ifndef _DEATHEVENT_HH_
#define _DEATHEVENT_HH_

#include <string>
#include "ievent.hh"
#include "debug.hh"

class Character;

// Event used to indicate the death of a character
class DeathEvent : public IEvent
{
	public:
		// Constructs a death event with the given attacker and victim.
		// Parameters:
		// Character* attacker - the attacking character
		// Character* victim - the killed character
		DeathEvent(Character* attacker, Character* victim);
		Character* getAttacker();
		Character* getVictim();
	private:
		Character* attacker;
		Character* victim;
};

#endif
