#include "rendersim.hh"
#include "debug.hh"
#include <cstdlib>

void debugConfig()
{
	#ifndef DEBUG
	Debug::getInstance()->setDebugStatus(false);
	#else
	Debug::getInstance()->setDebugStatus(true);
	Debug::getInstance()->setTerminalLogging(true);
	Debug::getInstance()->addChannel("RENDERSIM");
	Debug::getInstance()->addChannel("RANDLOCCHARSPAWN");
	Debug::getInstance()->addChannel("PATROLSTATE");
	Debug::getInstance()->addChannel("ATTACKSTATE");
	Debug::getInstance()->muteAllExcept("ATTACKSTATE");
	#endif
}

int main()
{
	std::srand(time(0));
	debugConfig();
	RenderSim* sim = new RenderSim();
	sim->config("gameconfig");
	sim->run();
}
