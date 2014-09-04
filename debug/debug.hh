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
		static const char* GAMEPLAY;
		static const char* WARN;
		static const char* ERROR;

	private:
		// Class is singleton, so the constructor, copy constructor, assignment operator, and deconstructor should be inaccessible.
		Debug(){};
		Debug(Debug const&){};
		Debug& operator=(Debug const&){};
		~Debug();
		static Debug* instance;
};

#endif
