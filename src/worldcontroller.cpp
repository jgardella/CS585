#include "worldcontroller.hh"

WorldController::WorldController(ASCIIRenderer* renderer)
{
	DEBUG_LOG("WORLDCONTROLLER", "Constructing new world controller.");
	this->renderer = renderer;
	Trie<IState*>* stateMap = new Trie<IState*>();
	stateMap->add("camera", new CameraState(renderer));
	machine = new StateMachine(stateMap, NULL, "camera");
}

void WorldController::tick(float dt)
{
	machine->tick(dt);
}
