#include "../include/debug.hh"

Debug* Debug::instance;

Debug::Debug()
{
	// construct channels array and add default channels
	channels = new t_channel[100];
	t_channel gameplay;
	gameplay.channelName = "GAMEPLAY";
	gameplay.isMuted = true;
	t_channel error;
	error.channelName = "ERROR";
	error.isMuted = true;
	t_channel warn;
	warn.channelName = "WARN";
	warn.isMuted = true;
	channels[0] = gameplay;
       	channels[1] = error;
	channels[2] = warn;	
	numChannels = 3;
	isTerminalLoggingEnabled = false;
	isFileLoggingEnabled = false;
	isNetworkLoggingEnabled = false;
}

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
	if(isUnmutedAndValid(channel) && enabled)
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
	if(numChannels < Debug::MAX_CHANNELS)
	{
		t_channel channel;
		channel.channelName = newChannel;
		channel.isMuted = false;	
		channels[numChannels++ - 1] = channel; // add new channel struct to list of custom channels
	}
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
	// iterate through channels and find specified channel
	for(i = 0; i < Debug::MAX_CHANNELS; i++)
	{
		if(channel.compare(channels[i].channelName) == 0)
		{
			return !channels[i].isMuted;
		}
	}
	// if this point is reached, the given channel name is not valid
	return false;
}

void Debug::setChannelMute(std::string channel, bool isChannelMuted)
{
	unsigned int i;
	for(i = 0; i < Debug::MAX_CHANNELS; i++)
	{
		if(channel.compare(channels[i].channelName) == 0)
		{
			channels[i].isMuted = isChannelMuted;
			return;
		}
	}
}

void Debug::muteAllExcept(std::string channel)
{
	unsigned int i;
	for(i = 0; i < Debug::MAX_CHANNELS; i++)
	{
		if(channel.compare(channels[i].channelName) != 0)
		{
			channels[i].isMuted = true;
		}
		else
		{
			channels[i].isMuted = false;
		}
	}
}
