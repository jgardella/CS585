#ifndef _DWARFFACTORY_HH_
#define _DWARFFACTORY_HH_

#include "dwarf.hh"
#include "dwarfcontroller.hh"

class DwarfFactory
{
	public:
		// Creates a new dwarf, registers it with the dwarf controller, and returns a reference.
		static Dwarf* get();

	private:
		DwarfController* controller;
};

#endif
