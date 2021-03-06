#include "selectstate.hh"

SelectState::SelectState(ASCIIRenderer* renderer) : WorldState(renderer)
{

}

void SelectState::tick(float dt)
{
	dispatcher->tick(dt);
}

void SelectState::parseInput(int c, bool keyDown)
{
	if(active && keyDown)
	{
		switch(c)
		{
			case 32: // space
				DEBUG_LOG("SELECTSTATE", "Unpausing and switching to inspection mode.");
				renderer->lockInspectOutput();
				if(renderer->getLockedActor() != NULL)
				{	
					MenuManager::getInstance()->setMenu(renderer->getLockedActor()->getType());
					active = false;
					renderer->setWorldState("INSPECT");
					dispatcher->dispatch(new StateEvent("inspect"));
				}
				else
				{
					renderer->unlockInspectOutput();
				}
				break;
			case KEY_LEFT:
				DEBUG_LOG("SELECTSTATE", "Moving cursor left.");
				renderer->moveCursorX(-1);
				break;
			case KEY_RIGHT:
				DEBUG_LOG("SELECTSTATE", "Moving cursor right.");
				renderer->moveCursorX(1);
				break;
			case KEY_UP:
				DEBUG_LOG("SELECTSTATE", "Moving cursor up.");
				renderer->moveCursorY(-1);
				break;
			case KEY_DOWN:
				DEBUG_LOG("SELECTSTATE", "Moving cursor down.");
				renderer->moveCursorY(1);
				break;
		}
	}
}
