#ifndef _ORCFACTORY_HH_
#define _ORCFACTORY_HH_

#include "orc.hh"
#include "orccontroller.hh"
#include "scenemanager.hh"

class OrcFactory
{
	public:
		// Creates a new orc and orc controller, registers the controller with the scene manager, and returns a reference to the orc.
		static Orc* get(int x, int y, unsigned int collisionLayer, unsigned int health);
};

#endif
