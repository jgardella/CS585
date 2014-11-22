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
		virtual std::string inspect();
		virtual bool sendKeyPress(int key, int cursorX, int cursorY);
	private:
		unsigned int teamNum;
		DynamicArray<SceneNode*>* sceneNodes;
};

#endif
