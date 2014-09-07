#include "debug.hh"

int main()
{
	Debug* debug = Debug::getInstance();
	
	debug->muteChannel(Debug::GAMEPLAY);
	
	Debug::log(Debug::GAMEPLAY, "Gameplay stuff 1.");
	
	debug->unmuteChannel(Debug::GAMEPLAY);

	Debug::log(Debug::GAMEPLAY, "Gameplay stuff 2.");
	
	debug->muteChannel(Debug::GAMEPLAY);

	Debug::log(Debug::GAMEPLAY, "Gameplay stuff 3.");

	return 0;
}
