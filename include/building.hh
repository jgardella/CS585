#ifndef _BUILDING_HH_
#define _BUILDING_HH_

#include "scenenode.hh"
#include "iactor.hh"
#include "dynamicarray.hh"
#include "buildingfunction.hh"
#include "sposition.hh"
#include "scenemanager.hh"

class Building : public IActor
{
	public:
		Building(std::string type, unsigned int corner1X, unsigned int corner1Y, unsigned int teamNum, Trie<double>* behavioralConfig, BuildingFunction* function);
	
		unsigned int getTeamNumber();
		DynamicArray<SceneNode*>* getSceneNodes();		
		
		int getEntranceX();
		int getEntranceY();
		tPosition* getNextAvailablePosition();
		virtual std::string inspect();
		virtual bool sendKeyPress(int key, int cursorX, int cursorY);
	private:
		int entranceX, entranceY;
		unsigned int corner1X, corner1Y;
		unsigned int teamNum;
		DynamicArray<SceneNode*>* sceneNodes;
		BuildingFunction* function;
};

#endif
