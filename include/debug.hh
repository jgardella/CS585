#ifndef _DEBUG_HH_
#define _DEBUG_HH_

#ifndef DEBUG_LOG
#define DEBUG_LOG Debug::getInstance()->log
#endif

#include <iostream>
#include <ctime>

// Struct for custom channels.
typedef struct s_channel
{
	std::string channelName;
	bool isMuted;
} t_channel;

class Debug
{
	public:
		// Instantiates the Debug singleton if it has not already been instantiated, and returns a pointer to the instantiated instance.
		// Returns a pointer to the instantiated instance.
		static Debug* getInstance();

		// Logs a message.
		// Parameters:
		// string channel - the channel to log the message in
		// string message - the message to log
		void log(std::string channel, std::string message);
		

		// Adds a new channel.
		// Parameters:
		// string newChannel - The name of the new channel. It is reccomended that this name be in all-caps.
		// Returns the name of the new channel so the user can pass it to log method. User should keep a reference to this name.
		std::string addChannel(std::string newChannel);

		// Sets the specified channel's mute value to the specified setting.
		// Parameters:
		// string channel - the channel to set the value of
		// bool isChannelMuted - the value to set the channel to
		void setChannelMute(std::string channel, bool isChannelMuted);
		
		// Mutes all channels except the one with the specified name. If the specified channel is currently muted, it will be unmuted.
		// Parameters:
		// string channel - the name of the channel to keep unmuted
		void muteAllExcept(std::string channel);
		
		// Mutes all channels except for the default channels (GAMEPLAY, ERROR, and WARN).
		void muteAllExceptDefault();

		// Unmutes all channels.
		void unmuteAll();

		// Enables/disables debug, based on the passed bool.
		// PArameters:
		// bool status - true to enable debug, false to disable debug
		void setDebugStatus(bool status);

		void setTerminalLogging(bool isOn);

		void setFileLogging(bool isOn);

		void setNetworkLogging(bool isOn);

	private:
		// Class is singleton, so the constructor, copy constructor, assignment operator, and deconstructor should be inaccessible.
		Debug();
		Debug(Debug const&);
		Debug& operator=(Debug const&);
		~Debug();
		static Debug* instance;
		static const unsigned int MAX_CHANNELS = 100;
		unsigned int numChannels;

		bool enabled;
		bool isTerminalLoggingEnabled;
		bool isFileLoggingEnabled;
		bool isNetworkLoggingEnabled;

		t_channel* channels;

		// Returns a timestamp representing the current time.
		std::string getTimestamp();

		// Checks if a channel is muted.
		// Parameters:
		// string channel - the channel to check the mute-status of
		// Returns true if channel is muted, false if not.
		bool isUnmutedAndValid(std::string channel);
};

#endif
