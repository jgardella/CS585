#include "rendersim.hh"
#include "debug.hh"

void debugConfig()
{
	#ifndef DEBUG
	Debug::getInstance()->setDebugStatus(false);
	#else
	Debug::getInstance()->setDebugStatus(true);
	Debug::getInstance()->setTerminalLogging(true);
	Debug::getInstance()->addChannel("RENDERSIM");
	#endif
}

int main()
{
	debugConfig();
	RenderSim* sim = new RenderSim();
	sim->config("data/gameconfig");
	sim->run();
}
