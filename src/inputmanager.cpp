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
}

void InputManager::addListener(IListenerCallback* callback)
{
	dispatcher->addListener("input", callback);
}

void InputManager::tick(float dt)
{
	dispatcher->dispatch(new InputEvent(getch()));
	dispatcher->tick(dt);
}
