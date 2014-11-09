#include "buildingfactory.hh"

Trie<tBuildingInfo*>* BuildingFactory::buildingInfos = new Trie<tBuildingInfo*>();
unsigned int BuildingFactory::id = 0;

Building* BuildingFactory::get(std::string type, unsigned int corner1X, unsigned int corner1Y, unsigned int teamNum)
{
	unsigned int i;
	tBuildingInfo* info = *buildingInfos->get("type");
	Building* building = new Building(corner1X, corner1Y, teamNum, info->behavioralConfig);
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
