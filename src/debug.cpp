#include "debug.hh"

Debug* Debug::instance;

Debug::Debug()
{
	// construct channels array and add default channels
	channels = new t_channel[100];
	t_channel gameplay;
	gameplay.channelName = "GAMEPLAY";
	gameplay.isMuted = false;
	t_channel error;
	error.channelName = "ERROR";
	error.isMuted = false;
	t_channel warn;
	warn.channelName = "WARN";
	warn.isMuted = false;
	channels[0] = gameplay;
       	channels[1] = error;
	channels[2] = warn;	
	numChannels = 3;
	recalculateMaxWidth();
	isTerminalLoggingEnabled = true;
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
	unsigned int i;
	int channelIndex;
	if((channelIndex = isUnmutedAndValid(channel)) >= 0 && enabled)
	{
		if(isTerminalLoggingEnabled)
		{
			setColor(channelIndex % 7 + 31);
			std::cout << channel;
			for(i = maxWidth; i > channel.length(); i--) // print out extra whitespace after channel
			{
				std::cout << " ";
			}	
			std::cout << " :: " << getTimestamp() << " :: " << message;
			setColor(37);
			std::cout << std::endl;
		}
		if(isFileLoggingEnabled)
		{
			debugfile << channel;
			for(i = maxWidth; i > channel.length(); i--) // print out extra whitespace after channel
			{
				debugfile << " ";
			}	
			debugfile << " :: " << getTimestamp() << " :: " << message << std::endl;
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
	debugfile.open("debugout");
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
		channels[numChannels++] = channel; // add new channel struct to list of custom channels
	}
	recalculateMaxWidth();
	return newChannel;
}

std::string Debug::getTimestamp()
{
	time_t rawTime;
	time(&rawTime); // stores current time in rawTime
	std::string stringTime = ctime(&rawTime); // converts time to string format
	return stringTime.substr(0, stringTime.length() - 1); // removes last character before turning, because ctime always appends a new-line to the end of the time
}

int Debug::isUnmutedAndValid(std::string channel)
{
	unsigned int i;
	// iterate through channels and find specified channel
	for(i = 0; i < numChannels; i++)
	{
		if(channel.compare(channels[i].channelName) == 0)
		{
			if(!channels[i].isMuted)
			{
				return i;
			}
		}
	}
	// if this point is reached, the given channel name is not valid
	return -1;
}

void Debug::setChannelMute(std::string channel, bool isChannelMuted)
{
	unsigned int i;
	for(i = 0; i < numChannels; i++)
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
	for(i = 0; i < numChannels; i++)
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

void Debug::unmuteAll()
{
	unsigned int i;
	for(i = 0; i < numChannels; i++)
	{
		channels[i].isMuted = false;
	}
}

void Debug::muteAllExceptDefault()
{
	unsigned int i;
	channels[0].isMuted = false;
	channels[1].isMuted = false;
	channels[2].isMuted = false;
	for(i = 3; i < numChannels; i++)
	{
		channels[i].isMuted = true;
	}
}

void Debug::recalculateMaxWidth()
{
	unsigned int maxLength = channels[0].channelName.length();
	unsigned int i;
	for(i = 0; i < numChannels; i++)
	{
		if(channels[i].channelName.length() > maxLength)
		{
			maxLength = channels[i].channelName.length();
		}
	}
	maxWidth = maxLength;
}

void Debug::setColor(int index)
{
	std::cout << "\x1b[" << index << "m";
}
