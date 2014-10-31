#include "characterfactory.hh"

Trie<tCharacterInfo*>* CharacterFactory::characterInfos;

Character* CharacterFactory::get(std::string type, int x, int y)
{
	unsigned int i;
	DynamicArray<std::string>* keys;
	Character* actor = NULL;
	ITickable* controller;
	StateMachine* machine;
	tCharacterInfo* info = *characterInfos->get(type);

	// create state machine
	machine = new StateMachine(info->stateMap, info->behavioralConfig, info->startState);
	
	// create actor
	actor = new Character(x, y, 1, info->health, info->type);
	
	// register state machine's listener with states in state map
	keys = info->stateMap->getKeys();
	for(i = 0; i < keys->length(); i++)
	{
		(*info->stateMap->get(*keys->get(i)))->addListener("state", machine->getListener());
		(*info->stateMap->get(*keys->get(i)))->setConfig(info->behavioralConfig);
		(*info->stateMap->get(*keys->get(i)))->setActor(actor);
	}
	
	// create controller
	controller = new CharacterController(actor, machine);
	
	// register actor's scenenode and controller with scene manager
	SceneManager::getInstance()->addTickable(controller);
	SceneManager::getInstance()->addSceneNode(actor->getSceneNode());
	return actor;
}

void CharacterFactory::addCharacterInfo(std::string name, tCharacterInfo* info)
{
	characterInfos->add(name, info);
}
