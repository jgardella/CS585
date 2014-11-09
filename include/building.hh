#ifndef _BUILDING_HH_
#define _BUILDING_HH_

#include "scenenode.hh"
#include "iactor.hh"
#include "dynamicarray.hh"

class Building : public IActor
{
	public:
		Building(unsigned int corner1X, unsigned int corner1Y, unsigned int teamNum, Trie<double>* behavioralConfig);
	
		unsigned int getTeamNumber();
		void getEntrance(int& x, int& y);
		DynamicArray<SceneNode*>* getSceneNodes();		
	private:
		unsigned int teamNum;
		unsigned int entranceX, entranceY;
		DynamicArray<SceneNode*>* sceneNodes;
};

#endif
