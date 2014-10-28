#include "orcfactory.hh"

Orc* OrcFactory::get(int x, int y, unsigned int collisionLayer, unsigned int health)
{
	Orc* orc = new Orc(x, y, collisionLayer, health);
	OrcController* controller = new OrcController(orc);
	SceneManager::getInstance()->addTickable(controller);
	return orc;
}
