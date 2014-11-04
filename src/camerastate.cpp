#include "camerastate.hh"

CameraState::CameraState(ASCIIRenderer* renderer) : WorldState(renderer)
{

}

void CameraState::tick(float dt)
{

}

void CameraState::parseInput(int c)
{
	DEBUG_LOG("CAMERASTATE", "Parsing input character: " + std::to_string(c) + ".");
	switch(c)
	{
		case 32: // space
			DEBUG_LOG("CAMERASTATE", "Pausing and switching to selection mode.");
			SceneManager::getInstance()->pause();
			dispatcher->dispatch(new StateEvent("select"));
			break;
		case KEY_LEFT:
			DEBUG_LOG("CAMERASTATE", "Moving camera left.");
			renderer->moveX(-1);
			break;
		case KEY_RIGHT:
			DEBUG_LOG("CAMERASTATE", "Moving camera right.");
			renderer->moveX(1);
			break;
		case KEY_UP:
			DEBUG_LOG("CAMERASTATE", "Moving camera up.");
			renderer->moveY(-1);
			break;
		case KEY_DOWN:
			DEBUG_LOG("CAMERASTATE", "Moving camera down.");
			renderer->moveY(1);
			break;
	}
}
