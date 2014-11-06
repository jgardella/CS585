#include "irenderer.hh"

IRenderer::IRenderer(int x, int y, int fps) : renderX(x), renderY(y)
{
	secPerFrame = 1.0 / fps;
	timeChange = 0;
}

void IRenderer::tick(float dt)
{
	timeChange += dt;
	if(timeChange >= secPerFrame)
	{
		render();
		timeChange = 0;
	}
}
