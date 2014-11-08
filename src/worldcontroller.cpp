#include "worldcontroller.hh"

WorldController::WorldController(ASCIIRenderer* renderer)
{
	DEBUG_LOG("WORLDCONTROLLER", "Constructing new world controller.");
	this->renderer = renderer;
	CameraState* cameraState = new CameraState(renderer);
	SelectState* selectState = new SelectState(renderer);
	InspectState* inspectState = new InspectState(renderer);
	Trie<IState*>* stateMap = new Trie<IState*>();
	stateMap->add("camera", cameraState);
	stateMap->add("select", selectState);
	stateMap->add("inspect", inspectState);
	machine = new StateMachine(stateMap, NULL, "camera");
	cameraState->addListener("state", machine->getListener());
	selectState->addListener("state", machine->getListener());
	inspectState->addListener("state", machine->getListener());
}

void WorldController::tick(float dt)
{
	machine->tick(dt);
}
