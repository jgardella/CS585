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
		// std::string type - the type of the character
		Character(int x, int y, unsigned int collisionLayer, unsigned int health, std::string type);

		// Deconstructs the character.
		~Character();

		void setX(int x);

		void setY(int y);

		int getX();
		
		int getY();

		SceneNode* getSceneNode();

		std::string getType();

	private:
		unsigned int health;
		std::string type;
		const unsigned int MAX_ATTACK = 25;
		SceneNode *sceneNode;

};

#endif
