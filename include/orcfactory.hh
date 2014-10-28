#ifndef _ORCFACTORY_HH_
#define _ORCFACTORY_HH_

#include "orc.hh"
#include "orccontroller.hh"

class OrcFactory
{
	public:
		// Creates a new orc, registers it with the orc controller, and returns a reference to it.
		static Orc* get();
	private:
		static OrcController* controller;
};

#endif
