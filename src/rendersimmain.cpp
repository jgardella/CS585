#include "rendersim.hh"

int main()
{
	RenderSim* sim = new RenderSim();
	sim->config("data/gameconfig");
	sim->run();
}
