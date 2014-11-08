#include "inputmanager.hh"

InputManager* InputManager::instance;

InputManager* InputManager::getInstance()
{
	if(instance == NULL)
	{
		instance = new InputManager();
	}
	return instance;
}

InputManager::InputManager()
{
	dispatcher = new Dispatcher();
	keyDown = 0;
}

void InputManager::addListener(IListenerCallback* callback)
{
	dispatcher->addListener("input", callback);
}

void InputManager::tick(float dt)
{
	static int ch;
	ch = getch();
	DEBUG_LOG("INPUTMANAGER", "Input manager read character " + std::to_string(ch) + ".");
	if(keyDown == 0 && ch != ERR) // keydown
	{
		keyDown = ch;
		dispatcher->dispatch(new InputEvent(ch, true));
	}
	else
	{
		if(keyDown != 0 && keyDown != ch) // key up
		{
			dispatcher->dispatch(new InputEvent(ch, false));
			keyDown = 0;
		}
	}
	dispatcher->tick(dt);
}
