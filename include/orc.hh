#ifndef _ORC_HH_
#define _ORC_HH_

#include "scenenode.hh"

class Orc : public IActor
{
	public:
		// Constructs a new orc.
		// Parameters:
		// int x - the initial x coordinate of the orc
		// int y - the initial y coordinate of the orc
		// unsigned int collisionLayer - layer on which the orc collides
		// unsigned int health - initial health of the orc
		Orc(int x, int y, unsigned int collisionLayer, unsigned int health);

		// Deconstructs the orc.
		~Orc();

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
