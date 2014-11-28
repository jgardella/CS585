#include "characterfactory.hh"

Trie<tCharacterInfo*>* CharacterFactory::characterInfos = new Trie<tCharacterInfo*>();
unsigned int CharacterFactory::id = 0;

Character* CharacterFactory::get(std::string type, int x, int y)
{
	unsigned int i;
	DynamicArray<std::string>* keys;
	Character* actor;
	CharacterController* controller;
	StateMachine* machine;
	IState* state;
	tCharacterInfo* info = *characterInfos->get(type);
	

	unsigned int gold;
	if(info->maxGold != info->minGold)
	{	
		gold = std::rand() % (info->maxGold - info->minGold) + info->minGold;
	}
	else
	{
		gold = info->maxGold;
	}

	// create actor
	actor = new Character(x, y, 1, id++, info->health, gold, info->hydration, info->energy, info->type, info->behavioralConfig, info->teamNum);
	DEBUG_LOG("CHARACTERFACTORY", "Hydration: " + std::to_string(info->hydration) + ", Energy: " + std::to_string(info->energy));
	PatrolState* patrolState = new PatrolState(actor);
	AttackState* attackState = new AttackState(actor);
	MoveToState* moveToState = new MoveToState(actor);
	SleepState* sleepState = new SleepState(actor);
	DrinkState* drinkState = new DrinkState(actor);

	Trie<IState*>* stateMap = new Trie<IState*>();
	stateMap->add("patrol", patrolState);
	stateMap->add("attack", attackState);
	stateMap->add("moveto", moveToState);
	stateMap->add("sleep", sleepState);
	stateMap->add("drink", drinkState);

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
	controller = new CharacterController(actor, machine, actor->getID());
	LevelManager::getInstance()->addControllerForCharacter(controller);
	actor->addListener("death", LevelManager::getInstance()->getLevelListener());

	// register actor's scenenode and controller with scene manager
	SceneManager::getInstance()->addSceneNode(actor->getSceneNode());
	SceneManager::getInstance()->addTickable(controller);
	return actor;
}

void CharacterFactory::addCharacterInfo(std::string name, tCharacterInfo* info)
{
	characterInfos->add(name, info);
}
