#ifndef _ACTOR_HH_
#define _ACTOR_HH_

#include "scenemanager.hh"
#include "scenenode.hh"
#include <string>

// Actor class for simulation.
class Actor
{
	public:
		// Constructs an actor with name, initial X and Y coordinate, and whether or not it collides.
		// Parameters:
		// std::string name - name of actor
		// int x - initial x coordinate of actor
		// int y - intial y coordinate of actor
		// bool collides - whether or not the actor collides with other collidable objects
		Actor(std::string name, int x, int y, bool collides);
		// Destructs an actor.
		~Actor();
		
		std::string getName();
		SceneNode* getSceneNode();
	private:
		std::string name;
		SceneNode *sceneNode;
};

#endif