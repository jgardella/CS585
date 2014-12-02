#ifndef _DRINKSTATE_HH_
#define _DRINKSTATE_HH_

#include "istate.hh"
#include "debug.hh"
#include "character.hh"
#include "building.hh"
#include "iactor.hh"
#include "levelmanager.hh"

class DrinkState : public IState
{
	public:
		DrinkState(Character* character);
		void tick(float dt);
		void moveToHome();
	private:
		Building* home;
		Character* character;
		bool isDrinking;

		void buyDrink();
};

#endif
