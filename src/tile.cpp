#include "tile.hh"

Tile::Tile(int x, int y, unsigned int collisionLayer, std::string type) : IActor(collisionLayer, "TILE", NULL)
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

std::string Tile::getType()
{
	return type;
}

SceneNode* Tile::getSceneNode()
{
	return sceneNode;
}

std::string Tile::inspect()
{
	return "Tile Type: " + type + "\n";
}
