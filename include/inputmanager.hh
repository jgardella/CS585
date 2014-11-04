#ifndef _INPUTMANAGER_HH_
#define _INPUTMANAGER_HH_

#include "dispatcher.hh"
#include "ilistenercallback.hh"
#include <ncurses.h>

class InputManager
{
	public:
		static InputManager* getInstance();

		void tick(float dt);
		
		void addListener(IListenerCallback* callback);

	private:
		InputManager();
		InputManager(InputManager const&);
		InputManager& operator=(InputManager const&);
		~InputManager();
		
		static InputManager* instance;
		Dispatcher* dispatcher;
};

#endif
