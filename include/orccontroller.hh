#ifndef _ORCCONTROLLER_HH_
#define _ORCCONTROLLER_HH_

#include "dynamicarray.hh"
#include "orc.hh"
#include "itickable.hh"

class OrcController : public ITickable
{
	public:
		OrcController(Orc* orc);
	
		void tick(float dt);

	private:
		Orc* orc;
		StateMachine* machine;
		float timeCounter;
		const int walkdt = 1; 
};

#endif
