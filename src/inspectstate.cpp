#include "inspectstate.hh"

InspectState::InspectState(ASCIIRenderer* renderer) : WorldState(renderer)
{

}

void InspectState::tick(float dt)
{
	dispatcher->tick(dt);
}

void InspectState::parseInput(int c, bool keyDown)
{
	if(active && keyDown)
	{
		switch(c)
		{
			case 32: // space
				DEBUG_LOG("INSPECTSTATE", "Unpausing and switching to camera mode.");
				SceneManager::getInstance()->unpause();
				active = false;
				curs_set(FALSE);
				dispatcher->dispatch(new StateEvent("camera"));
				break;
			case KEY_LEFT:
				break;
			case KEY_RIGHT:
				break;
			case KEY_UP:
				break;
			case KEY_DOWN:
				break;
		}
	}
}
