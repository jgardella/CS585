#ifndef _ACTOR_HH_
#define _ACTOR_HH_

#include "scenenode.hh"
#include <string>

class Actor
{
	public:
		Actor(std::string, int, int, int);
		std::string getName();
		SceneNode* getSceneNode();
	private:
		std::string name;
		SceneNode *sceneNode;
};

#endif
