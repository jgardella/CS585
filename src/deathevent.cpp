#include "deathevent.hh"

DeathEvent::DeathEvent(Character* attacker, Character* victim) : IEvent("death")
{
	DEBUG_LOG("DEATHEVENT", "Constructing death event.");
	this->attacker = attacker;
	this->victim = victim;
}

Character* DeathEvent::getAttacker()
{
	return attacker;
}

Character* DeathEvent::getVictim()
{
	return victim;
}
