#ifndef _DEBUG_HH_
#define _DEBUG_HH_

#define NULL 0

#include <iostream>

class Debug
{
	public:
		// Instantiates the Debug singleton if it has not already been instantiated, and returns a pointer to the instantiated instance.
		// Returns a pointer to the instantiated instance.
		Debug* getInstance();

		// Logs a message.
		// Parameters:
		// char* channel - the channel to log the message in
		// char* message - the message to log
		void log(char* channel, char* message);

		// Mutes a channel so that any messages logged to it are not displayed.
		// Parameters:
		// char* channel - the channel to mute
		void muteChannel(char* channel);
		
		// Channels
		static const char* GAMEPLAY = "GAMEPLAY";
		static const char* WARN = "WARN";
		static const char* ERROR = "ERROR";

	private:
		// Class is singleton, so the constructor, copy constructor, assignment operator, and deconstructor should be inaccessible.
		Debug(){};
		Debug(Debug const&){};
		Debug& operator=(Debug const&){};
		~Debug();
		static Debug* instance;
		

		// Returns a timestamp representing the current time.
		char* getTimestamp();

		// Checks if a channel is valid.
		// Parameters:
		// char* channel - the channel to check the validity of
		// Returns true if the channel is valid (i.e. defined as a static const char* in Debug), false if not.
		bool isValidChannel(char* channel);

		// Checks if a channel is muted.
		// Parameters:
		// char* channel - the channel to check the mute-status of
		// Returns true if channel is muted, false if not.
		bool isMuted(char* channel);
};

#endif
