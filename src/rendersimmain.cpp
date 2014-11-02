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
	Debug::getInstance()->addChannel("RANDLOCCHARSPAWN");
	Debug::getInstance()->addChannel("PATROLSTATE");
	Debug::getInstance()->addChannel("ATTACKSTATE");
	Debug::getInstance()->addChannel("FIXEDGRID");
	Debug::getInstance()->muteAllExcept("FIXEDGRID");
	Debug::getInstance()->setChannelMute("ATTACKSTATE", false);
	#endif
}

int main()
{
	debugConfig();
	RenderSim* sim = new RenderSim();
	sim->config("gameconfig");
	sim->run();
}
