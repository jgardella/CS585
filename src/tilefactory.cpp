#include "tilefactory.hh"

Trie<tTileInfo*>* TileFactory::tileInfos;

Tile* TileFactory::get(std::string type, int x, int y)
{
	tTileInfo* info = *tileInfos->get(type);

	Tile* tile = new Tile(x, y, info->collides, type);
	SceneManager::getInstance()->addSceneNode(tile->getSceneNode());
	return tile;
}

void TileFactory::addTileInfo(std::string type, tTileInfo* info)
{
	tileInfos->add(type, info);
}
