#ifndef _BUILDINGFACTORY_HH_
#define _BUILDINGFACTORY_HH_

#include "building.hh"
#include "buildinginfo.hh"
#include "dynamicarray.hh"
#include "trie.hh"
#include "scenenode.hh"
#include "scenemanager.hh"

class BuildingFactory
{
	public:
		static Building* get(unsigned int corner1X, unsigned int corner1Y, unsigned int corner2X, unsigned int corner2Y, unsigned int teamNum, unsigned int entranceX, unsigned int entranceY);
	
		static void addBuildingInfo(std::string name, tBuildingInfo* info);

	private:
		static Trie<tBuildingInfo*>* buildingInfos;
		static unsigned int id;
};

#endif
