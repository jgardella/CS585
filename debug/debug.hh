#ifndef _DEBUG_HH_
#define _DEBUG_HH_

class Debug
{
	public:
		Debug* getInstance();
		void log(char* channel, char* message);
		void muteChannel(char* channel);
	private:
		Debug(){};
		Debug(Debug const&){};
		Debug& operator=(Debug const&){};
		~Debug();
		static Debug* instance;
};

#endif
