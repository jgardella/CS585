#include "testgame.hh"
#include "debug.hh"

void debugInit()
{
	#ifndef DEBUG
	Debug::getInstance()->setDebugStatus(false);
	#else
	Debug::getInstance()->setDebugStatus(true);
	Debug::getInstance()->setTerminalLogging(true);
	Debug::getInstance()->addChannel("ACTOR");
	Debug::getInstance()->addChannel("SPAWNER");
	Debug::getInstance()->addChannel("MANAGER");
	Debug::getInstance()->addChannel("FIXEDGRID");
	Debug::getInstance()->addChannel("GAMEOBJ");
	Debug::getInstance()->addChannel("WALKCONTROLLER");
	Debug::getInstance()->muteAllExceptDefault();
	#endif
}

int main()
{
	debugInit();
	TestGame *simulation = new TestGame();
	simulation->simulate();
	return 0;
}
