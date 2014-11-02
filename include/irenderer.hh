#ifndef _IRENDERER_HH_
#define _IRENDERER_HH_

#include "itickable.hh"

class IRenderer : public ITickable
{
	public:
		virtual void render() = 0;
		virtual void tick(float dt);
	protected:
		IRenderer(int x, int y, int fps);
		int renderX, renderY;
		float secPerFrame, timeChange;

};

#endif
