#include "tile.hh"

Tile::Tile(int x, int y, unsigned int collisionLayer, std::string type) : IActor(collisionLayer, type)
{
	sceneNode = new SceneNode(x, y, *this, NULL, NULL);
	this->type = type;
}

void Tile::setX(int x)
{
	sceneNode->setX(x);
}

void Tile::setY(int y)
{
	sceneNode->setY(y);
}

int Tile::getX()
{
	return sceneNode->getX();
}

int Tile::getY()
{
	return sceneNode->getY();
}

SceneNode* Tile::getSceneNode()
{
	return sceneNode;
}