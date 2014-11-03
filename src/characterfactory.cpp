#include "characterfactory.hh"

Trie<tCharacterInfo*>* CharacterFactory::characterInfos = new Trie<tCharacterInfo*>();
unsigned int CharacterFactory::id = 0;

Character* CharacterFactory::get(std::string type, int x, int y)
{
	unsigned int i;
	DynamicArray<std::string>* keys;
	Character* actor;
	ITickable* controller;
	StateMachine* machine;
	IState* state;
	tCharacterInfo* info = *characterInfos->get(type);
	// create actor
	actor = new Character(x, y, 1, id++, info->health, info->type);
	PatrolState* patrolState = new PatrolState(actor, info->behavioralConfig);
	AttackState* attackState = new AttackState(actor, info->behavioralConfig);

	
	Trie<IState*>* stateMap = new Trie<IState*>();
	stateMap->add("patrol", patrolState);
	stateMap->add("attack", attackState);


	// create state machine
	machine = new StateMachine(stateMap, info->behavioralConfig, info->startState);
	
	
	// register state machine's listener with states in state map
	keys = stateMap->getKeys();
	for(i = 0; i < keys->length(); i++)
	{
		state = *stateMap->get(*keys->get(i));
		state->addListener("state", machine->getListener());
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
