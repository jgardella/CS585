#include "dwarffactory.hh"

static Dwarf* get()
{
	Dwarf* dwarf = new Dwarf();
	controller->addDwarf(dwarf);
	return dwarf;
}
