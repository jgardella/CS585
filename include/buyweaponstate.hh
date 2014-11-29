#ifndef _BUYWEAPONSTATE_HH_
#define _BUYWEAPONSTATE_HH_

#include "istate.hh"
#include "character.hh"
#include "building.hh"
#include "levelmanager.hh"
#include "weaponfactory.hh"

class BuyWeaponState : public IState
{
	public:
		BuyWeaponState(Character* character);
		void tick(float dt);
		void moveToBlacksmith();
	private:
		bool isShopping;
		Character* character;
		Building* blacksmith;
};

#endif
