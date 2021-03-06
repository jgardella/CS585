#include "rendersim.hh"
#include "debug.hh"
#include <cstdlib>

void debugConfig()
{
	#ifndef DEBUG
	Debug::getInstance()->setDebugStatus(false);
	#else
	Debug::getInstance()->setDebugStatus(true);
	Debug::getInstance()->setTerminalLogging(false);
	Debug::getInstance()->setFileLogging(true);
	//Debug::getInstance()->addChannel("RENDERSIM");
	//Debug::getInstance()->addChannel("RANDLOCCHARSPAWN");
	Debug::getInstance()->addChannel("PATROLSTATE");
	Debug::getInstance()->addChannel("ATTACKSTATE");
	Debug::getInstance()->addChannel("DRINKSTATE");
	Debug::getInstance()->addChannel("LEVEL");
	//Debug::getInstance()->addChannel("FIXEDGRID");
	//Debug::getInstance()->addChannel("CHARACTER");
	//Debug::getInstance()->addChannel("CHARACTERFACTORY");
	//Debug::getInstance()->addChannel("CAMERASTATE");
	//Debug::getInstance()->addChannel("WORLDSTATE");
	//Debug::getInstance()->addChannel("SELECTSTATE");
	//Debug::getInstance()->addChannel("INSPECTSTATE");
	//Debug::getInstance()->addChannel("TILEFACTORY");
	//Debug::getInstance()->addChannel("LEVEL");
	//Debug::getInstance()->addChannel("ASCIIRENDERER");
	//Debug::getInstance()->addChannel("INPUTMANAGER");
	//Debug::getInstance()->addChannel("WORLDCONTROLLER");
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
