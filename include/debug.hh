#ifndef _DEBUG_HH_
#define _DEBUG_HH_

#include <iostream>
#include <ctime>
#include "dynamicarray.hh"

// Struct for custom channels.
typedef struct s_customChannel
{
	std::string channelName;
	bool isMuted;
} t_customChannel;

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
		static void log(std::string channel, std::string message);
		

		// Adds a new channel.
		// Parameters:
		// string newChannel - The name of the new channel. It is reccomended that this name be in all-caps.
		// Returns the name of the new channel so the user can pass it to log method. User should keep a reference to this name.
		std::string addChannel(std::string newChannel);

		// Mutes a channel so that any messages logged to it are not displayed.
		// Parameters:
		// string channel - the channel to mute
		void muteChannel(std::string channel);
		
		// Unmutes a channel.
		// Parameters:
		// string channel - the channel to unmute
		void unmuteChannel(std::string channel);

		// Channels
		static const std::string GAMEPLAY;
		static const std::string WARN;
		static const std::string ERROR;

	private:
		// Class is singleton, so the constructor, copy constructor, assignment operator, and deconstructor should be inaccessible.
		Debug(){};
		Debug(Debug const&){};
		Debug& operator=(Debug const&){};
		~Debug();
		static Debug* instance;
		
		static bool isGameplayMuted;
		static bool isWarnMuted;
		static bool isErrorMuted;
		
		static DynamicArray<t_customChannel>* addedChannels;

		// Returns a timestamp representing the current time.
		static std::string getTimestamp();

		// Checks if a channel is muted.
		// Parameters:
		// string channel - the channel to check the mute-status of
		// Returns true if channel is muted, false if not.
		static bool isUnmutedAndValid(std::string channel);
};

#endif
