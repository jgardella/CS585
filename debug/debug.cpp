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

void Debug::log(std::string channel, std::string message)
{
	if(isValidChannel(channel) && !isMuted(channel))
	{
		std::cout << channel << "::" << message << std::endl;
	}
}

bool Debug::isValidChannel(std::string channel)
{
	return channel.compare(Debug::GAMEPLAY) == 0 || channel.compare(Debug::WARN) == 0 || channel.compare(Debug::ERROR) == 0;
}

bool Debug::isMuted(std::string channel)
{
	if(channel.compare(Debug::GAMEPLAY) == 0)
	{
		return isGameplayMuted;
	}
	if(channel.compare(Debug::WARN) == 0)
	{
		return isWarnMuted;
	}
	return isErrorMuted;
}
