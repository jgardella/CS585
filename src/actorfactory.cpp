#include "actorfactory.hh"

IActor* ActorFactory::get(std::string type, int x, int y)
{
	IActor* actor;
	if(type.compare("orc") == 0)
	{
		actor = OrcFactory::get();
	}
	else if(type.compare("dwarf") == 0)
	{
		actor = DwarfFactory::get();
	}
	SceneManager::getInstance()->addSceneNode(actor->getSceneNode());
	return actor;
}
