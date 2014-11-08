#ifndef _DWARF_HH_
#define _DWARF_HH_

#include "scenenode.hh"
#include "dispatcher.hh"
#include "scenemanager.hh"

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
		Character(int x, int y, unsigned int collisionLayer, unsigned int id, unsigned int health, unsigned int gold, std::string type, Trie<double>* behavioralConfig);

		// Deconstructs the character.
		~Character();

		void setX(int x);

		void setY(int y);

		int getX();
		
		int getY();

		int getID();
		
		unsigned int getGold();

		void setGold(unsigned int newValue);
			
		int getHealth();

		SceneNode* getSceneNode();

		std::string getType();
		
		void takeDamage(unsigned int damage);
		
		void setTarget(Character* target);

		Character* getTarget();

		virtual std::string inspect();
		
	private:
		unsigned int health;
		unsigned int id;
		unsigned int gold;
		std::string type;
		SceneNode *sceneNode;
		Character* target;
};

#endif
