#include "buildingfactory.hh"

Trie<tBuildingInfo*>* BuildingFactory::buildingInfos = new Trie<tBuildingInfo*>();
unsigned int BuildingFactory::id = 0;

Building* BuildingFactory::get(unsigned int corner1X, unsigned int corner1Y, unsigned int corner2X, unsigned int corner2Y, unsigned int teamNum, unsigned int entranceX, unsigned int entranceY)
{
	unsigned int i;
	Building* building = new Building(corner1X, corner1Y, corner2X, corner2Y, teamNum, entranceX, entranceY);
	DynamicArray<SceneNode*>* nodes = building->getSceneNodes();
	for(i = 0; i < nodes->length(); i++)
	{
		SceneManager::getInstance()->addSceneNode(*nodes->get(i));
	}
	return building;
}

void BuildingFactory::addBuildingInfo(std::string name, tBuildingInfo* info)
{
	buildingInfos->add(name, info);
}
