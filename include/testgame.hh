#ifndef _TESTGAME_HH_
#define _TESTGAME_HH_

#include "gameobject.hh"
#include <ctime>

class TestGame
{
	public:
		TestGame();
		void simulate();
	private:
		GameObject *gameObject;
};

#endif
