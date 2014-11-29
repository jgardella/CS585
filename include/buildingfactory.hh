#ifndef _BUILDINGFACTORY_HH_
#define _BUILDINGFACTORY_HH_

#include "building.hh"
#include "buildinginfo.hh"
#include "buildingfactory.hh"
#include "dynamicarray.hh"
#include "trie.hh"
#include "scenenode.hh"
#include "scenemanager.hh"
#include "buildingfunction.hh"
#include "grandhallfunction.hh"
#include "blacksmithfunction.hh"

class BuildingFactory
{
	public:
		static Building* get(std::string type, unsigned int corner1X, unsigned int corner1Y, unsigned int teamNum);
	
		static void addBuildingInfo(std::string name, tBuildingInfo* info);

	private:
		static Trie<tBuildingInfo*>* buildingInfos;
		static unsigned int id;
};

#endif
