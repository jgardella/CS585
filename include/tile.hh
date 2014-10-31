#ifndef _TILE_HH_
#define _TILE_HH_

#include "scenenode.hh"

class Tile : public IActor
{
	public:
		Tile(int x, int y, unsigned int collisionLayer, std::string classType);
		
		void setX(int x);

		void setY(int y);

		int getX();
		
		int getY();

		SceneNode* getSceneNode();
	private:
		SceneNode* sceneNode;
		std::string type;
};

#endif