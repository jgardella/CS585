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
	timeChange = 0;
}

void InputManager::addListener(IListenerCallback* callback)
{
	dispatcher->addListener("input", callback);
}

void InputManager::tick(float dt)
{
	timeChange += dt;
	if(timeChange >= 1)
	{
		static int ch;
		ch = getch();
		if(ch != ERR)
		{
			DEBUG_LOG("INPUTMANAGER", "Input manager read character " + std::to_string(ch) + ".");
			dispatcher->dispatch(new InputEvent(ch));
		}
		dispatcher->tick(dt);
		timeChange = 0;
	}
}
