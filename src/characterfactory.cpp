#include "characterfactory.hh"

Trie<tCharacterInfo*>* CharacterFactory::characterInfos = new Trie<tCharacterInfo*>();

Character* CharacterFactory::get(std::string type, int x, int y)
{
	unsigned int i;
	DynamicArray<std::string>* keys;
	Character* actor;
	ITickable* controller;
	StateMachine* machine;
	IState* state;
	tCharacterInfo* info = *characterInfos->get(type);

	// create state machine
	machine = new StateMachine(info->stateMap, info->behavioralConfig, info->startState);
	
	// create actor
	actor = new Character(x, y, 1, info->health, info->type);

	// register state machine's listener with states in state map
	keys = info->stateMap->getKeys();
	for(i = 0; i < keys->length(); i++)
	{
		state = *info->stateMap->get(*keys->get(i));
		state->addListener("state", machine->getListener());
		state->setConfig(info->behavioralConfig);
		state->setActor(actor);
	}
	
	// create controller
	controller = new CharacterController(actor, machine);
	
	// register actor's scenenode and controller with scene manager
	SceneManager::getInstance()->addSceneNode(actor->getSceneNode());
	SceneManager::getInstance()->addTickable(controller);
	return actor;
}

void CharacterFactory::addCharacterInfo(std::string name, tCharacterInfo* info)
{
	characterInfos->add(name, info);
}
