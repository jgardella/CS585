#ifndef _ACTOR_HH_
#define _ACTOR_HH_

#include "scenemanager.hh"
#include "scenenode.hh"
#include "trie.hh"
#include <string>

// Actor class for simulation.
class Actor : public IActor
{
	public:
		// Constructs an actor with name, initial X and Y coordinate, and whether or not it collides.
		// Parameters:
		// std::string name - name of actor
		// int x - initial x coordinate of actor
		// int y - intial y coordinate of actor
		// unsigned int col - collision layer for actor
		Actor(std::string name, int x, int y, unsigned int col, Trie<double>* behavioralConfig);
		
		~Actor();

		void setX(int x);

		void setY(int y);
		
		int getX();

		int getY();
		
		void remove();

		bool isRemoved();

		std::string getName();
		
		SceneNode* getSceneNode();
		
		virtual std::string inspect();

	private:
		std::string name;
		SceneNode *sceneNode;
		bool removed;
};

#endif
