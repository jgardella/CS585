#include "debug.hh"

const std::string Debug::GAMEPLAY = "GAMEPLAY";
const std::string Debug::ERROR = "ERROR";
const std::string Debug::WARN = "WARN";

bool Debug::isGameplayMuted = false;
bool Debug::isWarnMuted = false;
bool Debug::isErrorMuted = false;

Debug* Debug::instance;

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
		std::cout << channel << " :: " << message << std::endl;
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

void Debug::muteChannel(std::string channel)
{
	if(channel.compare(Debug::GAMEPLAY) == 0)
	{
		isGameplayMuted = true;
	}
	else if(channel.compare(Debug::WARN) == 0)
	{
		isWarnMuted = true;
	}
	else if(channel.compare(Debug::ERROR) == 0)
	{
		isErrorMuted = true;
	}
}

void Debug::unmuteChannel(std::string channel)
{
	if(channel.compare(Debug::GAMEPLAY) == 0)
	{
		Debug::isGameplayMuted = false;
	}
	else if(channel.compare(Debug::WARN) == 0)
	{
		Debug::isWarnMuted = false;
	}
	else if(channel.compare(Debug::ERROR) == 0)
	{
		Debug::isErrorMuted = false;
	}
}
