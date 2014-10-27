#include "actorfactory.hh"

IActor* ActorFactory::get(std::string type, int x, int y)
{
	if(type.compare("orc") == 0)
	{
		return OrcFactory::get();
	}
	else if(type.compare("dwarf") == 0)
	{
		return DwarfFactory::get();
	}
}
