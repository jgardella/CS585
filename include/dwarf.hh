#ifndef _DWARF_HH_
#define _DWARF_HH_

#include "scenenode.hh"

class Dwarf : public IActor
{
	public:
		// Constructs a new dwarf.
		// Parameters:
		// int x - the initial x coordinate of the dwarf
		// int y - the initial y coordinate of the dwarf
		// unsigned int collisionLayer - layer on which the dwarf collides
		// unsigned int health - initial health of the dwarf
		Dwarf(int x, int y, unsigned int collisionLayer, unsigned int health);

		// Deconstructs the orc.
		~Dwarf();

		void setX(int x);

		void setY(int y);

		int getX();
		
		int getY();

		SceneNode* getSceneNode();


	private:
		unsigned int health;
		const unsigned int MAX_ATTACK = 25;
		SceneNode *sceneNode;
};

#endif
