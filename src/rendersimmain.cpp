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
	Debug::getInstance()->addChannel("JSON");
	Debug::getInstance()->addChannel("DYNAMICARRAY");
	Debug::getInstance()->addChannel("TRIE");
	Debug::getInstance()->addChannel("RANDLOCCHARSPAWN");
	#endif
}

int main()
{
	debugConfig();
	RenderSim* sim = new RenderSim();
	sim->config("gameconfig");
	sim->run();
}
