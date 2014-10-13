#ifndef _TESTGAME_HH_
#define _TESTGAME_HH_

#include "gameobject.hh"
#include <ctime>

class TestGame
{
	public:
		// Construct a new test game.
		TestGame();
		
		// Start the simulation.
		void simulate();
	private:
		GameObject *gameObject;
};

#endif
