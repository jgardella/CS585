#ifndef _DWARF_HH_
#define _DWARF_HH_

#include "scenenode.hh"
#include "dispatcher.hh"

class Character : public IActor
{
	public:
		// Constructs a new character.
		// Parameters:
		// int x - the initial x coordinate of the character
		// int y - the initial y coordinate of the character
		// unsigned int collisionLayer - layer on which the character collides
		// unsigned int health - initial health of the character
		Character(int x, int y, unsigned int collisionLayer, unsigned int health);

		// Deconstructs the character.
		~Character();

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
