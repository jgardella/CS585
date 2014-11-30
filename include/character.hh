#ifndef _CHARACTER_HH_
#define _CHARACTER_HH_

#include "scenenode.hh"
#include "dispatcher.hh"
#include "scenemanager.hh"
#include "sposition.hh"
#include "ilistenercallback.hh"
#include "dispatcher.hh"
#include "deathevent.hh"
#include "stateevent.hh"
#include "weapon.hh"
#include "weaponfactory.hh"
#include "armor.hh"
#include "armorfactory.hh"
#include "healthpotion.hh"

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
		Character(int x, int y, unsigned int collisionLayer, unsigned int id, unsigned int health, unsigned int gold, double hydration, double energy, std::string type, Trie<double>* behavioralConfig, unsigned int teamNum);

		// Deconstructs the character.
		~Character();

		void setX(int x);

		void setY(int y);

		int getX();
		
		int getY();

		unsigned int getID();
		
		unsigned int getGold();

		void setGold(unsigned int newValue);
			
		int getHealth();

		SceneNode* getSceneNode();

		std::string getType();
		
		void takeDamage(Character* attacker, unsigned int damage);
		
		void setTarget(Character* target);

		Character* getTarget();
		
		unsigned int getTeam();

		void setMoveLocation(int x, int y);
		
		void nullifyMoveLocation();
		
		tPosition* getMoveLocation();
		
		virtual std::string inspect();
		
		virtual bool sendKeyPress(int key, int cursorX, int cursorY);

		void addListener(std::string eventType, IListenerCallback* callback);
		
		void simulateNeeds();
		
		void sleep();

		bool hasMaxEnergy();
		
		void drink();

		bool hasMaxHydration();
		
		float getEnergy();
		
		float getHydration();

		float getProperty(std::string name);
		
		bool isDead();
		
		Weapon* getWeapon();

		Armor* getArmor();

		HealthPotion* getPotion();
		
		void setWeapon(Weapon* weapon);

		void setArmor(Armor* armor);

		void setPotion(HealthPotion* potion);

	private:
		unsigned int health;
		unsigned int id;
		unsigned int gold;
		unsigned int exp;
		unsigned int level;
		Weapon* weapon;
		Armor* armor;
		HealthPotion* potion;
		double hydration;
		double energy;
		bool dead;
		unsigned int teamNum;
		SceneNode *sceneNode;
		Character* target;
		tPosition* moveLocation;
		Dispatcher* dispatcher;
};

#endif
