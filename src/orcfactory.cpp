#include "orcfactory.hh"

Orc* OrcFactory::get()
{
	Orc* orc = new Orc();
	controller->addOrc(orc);
	return orc;
}
