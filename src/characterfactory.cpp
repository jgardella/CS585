#include "characterfactory.hh"

Character* CharacterFactory::get(std::string type, int x, int y)
{
	Character* actor = NULL;
	ITickable* controller;
	if(type.compare("orc") == 0)
	{
		actor = new Character(x, y, 1, 25);
		controller = new OrcController(actor);
	}
	else if(type.compare("dwarf") == 0)
	{
		actor = new Character(x, y, 1, 50);
		controller = new DwarfController(actor);
	}
	SceneManager::getInstance()->addTickable(controller);
	SceneManager::getInstance()->addSceneNode(actor->getSceneNode());
	return actor;
}
