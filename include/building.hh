#ifndef _BUILDING_HH_
#define _BUILDING_HH_

#include "scenenode.hh"
#include "iactor.hh"
#include "dynamicarray.hh"

class Building : public IActor
{
	public:
		Building(std::string type, unsigned int corner1X, unsigned int corner1Y, unsigned int teamNum, Trie<double>* behavioralConfig);
	
		unsigned int getTeamNumber();
		DynamicArray<SceneNode*>* getSceneNodes();		
		std::string getType();
	private:
		unsigned int teamNum;
		std::string type;
		DynamicArray<SceneNode*>* sceneNodes;
};

#endif
