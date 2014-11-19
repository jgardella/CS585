#include "building.hh"

Building::Building(std::string type, unsigned int corner1X, unsigned int corner1Y, unsigned int teamNum, Trie<double>* behavioralConfig) : IActor(1, "BUILDING", behavioralConfig)
{
	unsigned int i;
	unsigned int width = *behavioralConfig->get("width");
	unsigned int height = *behavioralConfig->get("height");
	this->teamNum = teamNum;
	this->sceneNodes = new DynamicArray<SceneNode*>();
	this->type = type;
	for(i = corner1X; i <= width + corner1X; i++)
	{
		sceneNodes->pushBack(new SceneNode(i, corner1Y, *this, NULL, NULL));
		sceneNodes->pushBack(new SceneNode(i, corner1Y + width, *this, NULL, NULL));
	}

	for(i = corner1Y + 1; i < height + corner1Y; i++)
	{
		sceneNodes->pushBack(new SceneNode(corner1X, i, *this, NULL, NULL));
		sceneNodes->pushBack(new SceneNode(corner1X + height, i, *this, NULL, NULL));
	}

	setType(type);
}

unsigned int Building::getTeamNumber()
{
	return teamNum;
}

DynamicArray<SceneNode*>* Building::getSceneNodes()
{
	return sceneNodes;
}
