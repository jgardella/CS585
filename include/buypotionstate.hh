#ifndef _BUYPOTIONSTATE_HH_
#define _BUYPOTIONSTATE_HH_

#include "istate.hh"
#include "character.hh"
#include "building.hh"
#include "levelmanager.hh"
#include "healthpotionfactory.hh"

class BuyPotionState : public IState
{
	public:
		BuyPotionState(Character* character);
		void tick(float dt);
		void moveToApothecary();
	private:
		bool isShopping;
		Character* character;
		Building* apothecary;
};

#endif
