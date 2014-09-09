#include "../include/debug.hh"

const std::string Debug::GAMEPLAY = "GAMEPLAY";
const std::string Debug::ERROR = "ERROR";
const std::string Debug::WARN = "WARN";

bool Debug::isGameplayMuted = false;
bool Debug::isWarnMuted = false;
bool Debug::isErrorMuted = false;

bool Debug::isTerminalLoggingEnabled = false;
bool Debug::isFileLoggingEnabled = false;
bool Debug::isNetworkLoggingEnabled = false;

Debug* Debug::instance;

DynamicArray<t_customChannel>* Debug::addedChannels = new DynamicArray<t_customChannel>();

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
	if(isUnmutedAndValid(channel))
	{
		if(isTerminalLoggingEnabled)
		{
			std::cout << channel << " :: " << getTimestamp() << " :: " << message << std::endl;
		}
		if(isFileLoggingEnabled)
		{
			// file logging implementation
		}
		if(isNetworkLoggingEnabled)
		{
			// network logging implementation
		}
	}
}

void Debug::setDebugStatus(bool status)
{
	enabled = status;
}

void Debug::setTerminalLogging(bool isOn)
{
	isTerminalLoggingEnabled = isOn;
}

void Debug::setFileLogging(bool isOn)
{
	isFileLoggingEnabled = isOn;
}

void Debug::setNetworkLogging(bool isOn)
{
	isNetworkLoggingEnabled = isOn;
}

std::string Debug::addChannel(std::string newChannel)
{
	t_customChannel customChannel;
	customChannel.channelName = newChannel;
	customChannel.isMuted = false;	
	addedChannels->pushBack(customChannel); // add new channel struct to list of custom channels
	return newChannel;
}

std::string Debug::getTimestamp()
{
	time_t rawTime;
	time(&rawTime); // stores current time in rawTime
	std::string stringTime = ctime(&rawTime); // converts time to string format
	return stringTime.substr(0, stringTime.length() - 1); // removes last character before turning, because ctime always appends a new-line to the end of the time
}

bool Debug::isUnmutedAndValid(std::string channel)
{
	unsigned int i;
	if(channel.compare(Debug::GAMEPLAY) == 0)
	{
		return !isGameplayMuted;
	}
	if(channel.compare(Debug::WARN) == 0)
	{
		return !isWarnMuted;
	}
	if(channel.compare(Debug::ERROR) == 0)
	{
		return !isErrorMuted;
	}
	// channel is not any of the default channels, check custom channels
	for(i = 0; i < addedChannels->length(); i++)
	{
		t_customChannel customChannel = addedChannels->get(i);
		if(channel.compare(customChannel.channelName) == 0)
		{
			return !customChannel.isMuted;
		}
	}
	// if this point is reached, the given channel name is not valid
	return false;
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
