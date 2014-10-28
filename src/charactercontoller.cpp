#include "charactercontroller.hh"

CharacterController::CharacterController(Character* character, Trie<IState*>* map, Trie<float>* config, std::string startState)
{
	unsigned int i;
	DynamicArray<std::string>* keys;
	this->character = character;
	machine = new StateMachine(map, config, startState);
	// register state machine's listener with states in state map
	keys = map->getKeys();
	for(i = 0; i < keys->length(); i++)
	{
		(*map->get(*keys->get(i)))->addListener("state", machine->getListener());
	}
}

void CharacterController::tick(float dt)
{

}
