#include "actorfactory.hh"

IActor* ActorFactory::get(std::string type, int x, int y)
{
	IActor* actor;
	ITickable* controller;
	if(type.compare("orc") == 0)
	{
		actor = new Orc(x, y, collisionLayer, health);
		controller = new OrcController((Orc*)actor);
	}
	else if(type.compare("dwarf") == 0)
	{
		actor = new Dwarf(x, y, collisionLayer, health);
		controller = new DwarfController((Dwarf*)actor);
	}
	SceneManager::getInstance()->addTickable(controller);
	SceneManager::getInstance()->addSceneNode(actor->getSceneNode());
	return actor;
}
