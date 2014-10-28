#include "actorfactory.hh"

IActor* ActorFactory::get(std::string type, int x, int y)
{
	IActor* actor;
	ITickable* controller;
	if(type.compare("orc") == 0)
	{
		actor = new Character(x, y, 1, 50);
		controller = new OrcController(actor);
	}
	else if(type.compare("dwarf") == 0)
	{
		actor = new Character(x, y, 1, h);
		controller = new DwarfController(actor);
	}
	SceneManager::getInstance()->addTickable(controller);
	SceneManager::getInstance()->addSceneNode(actor->getSceneNode());
	return actor;
}
