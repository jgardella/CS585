#ifndef _BUYARMORSTATE_HH_
#define _BUYARMORSTATE_HH_

#include "istate.hh"
#include "character.hh"
#include "building.hh"
#include "levelmanager.hh"
#include "armorfactory.hh"
#include "buyarmorstate.hh"

class BuyArmorState : public IState
{
	public:
		BuyArmorState(Character* character);
		void tick(float dt);
		void moveToBlacksmith();
	private:
		bool isShopping;
		Character* character;

		void buyArmor();
};

#endif
