#ifndef _ITICKABLE_HH_
#define _ITICKABLE_HH_

// Interface to classes which are tickable.
class ITickable
{
	public:
		virtual void tick(float dt) = 0;
};

#endif
