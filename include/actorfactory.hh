#ifndef _ACTORFACTORY_HH_
#define _ACTORFACTORY_HH_

#include "iactor.hh"
#include "scenemanager.hh"
#include "character.hh"

class ActorFactory
{
	public:

		// Creates a new actor of the given type and places it at the given coordinates in the world. Returns a reference to the actor.
		// Parameters:
		// std::string type - the type of the actor
		// int x - the x coordinate at which to instantiate the actor
		// int y - the y coordinate at which to instatiate the actor
		static IActor* get(std::string type, int x, int y);
};

#endif
