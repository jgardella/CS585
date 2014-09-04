#include "debug.hh"

Debug* Debug::getInstance()
{
	// instantiate instance if it has not been instantiated
	if(instance == NULL)
	{
		instance = new Debug();
	}
	return instance;
}

void Debug::log(char* channel, char* message)
{
	if(isValidChannel(channel) && !isMuted(channel))
	{
		std::cout << channel << "::" << getTimestamp() << "::" << message << std::endl;
	}
}
