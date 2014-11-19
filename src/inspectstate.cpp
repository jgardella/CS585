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
	IActor* actorUnderCursor;
	if(active && keyDown)
	{
		switch(c)
		{
			case 32: // space
				DEBUG_LOG("INSPECTSTATE", "Unpausing and switching to camera mode.");
				SceneManager::getInstance()->unpause();
				active = false;
				curs_set(FALSE);
				renderer->lockInspectOutput();
				dispatcher->dispatch(new StateEvent("camera"));
				MenuManager::getInstance()->disableMenu();
				break;
			case 'm':
				DEBUG_LOG("INSPECTSTATE", "Issuing move command to dwarf.");
				actorUnderCursor = renderer->getLockedActor();
				if(actorUnderCursor != NULL && actorUnderCursor->getClass().compare("CHARACTER") == 0 && ((Character*)actorUnderCursor)->getType().compare("dwarf") == 0)
				{
					LevelManager::getInstance()->getControllerForCharacter(((Character*)actorUnderCursor)->getID())->issueMoveCommand(renderer->getCursorWorldX(), renderer->getCursorWorldY());
				}
				break;
			case KEY_LEFT:
				DEBUG_LOG("INSPECTSTATE", "Moving cursor left.");
				renderer->moveCursorX(-1);
				break;
			case KEY_RIGHT:
				DEBUG_LOG("INSPECTSTATE", "Moving cursor right.");
				renderer->moveCursorX(1);
				break;
			case KEY_UP:
				DEBUG_LOG("INSPECTSTATE", "Moving cursor up.");
				renderer->moveCursorY(-1);
				break;
			case KEY_DOWN:
				DEBUG_LOG("INSPECTSTATE", "Moving cursor down.");
				renderer->moveCursorY(1);
				break;
		}
	}
}
