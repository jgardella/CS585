#include "tilefactory.hh"

Tile* TileFactory::get(std::string type, int x, int y)
{
	Tile* tile = new Tile(x, y, 0, type);
	SceneManager::getInstance()->addSceneNode(tile->getSceneNode());
	return tile;
}
