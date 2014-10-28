#include "characterfactory.hh"

Trie<Trie<IState*>*>* CharacterFactory::stateMaps;
Trie<Trie<float>*>* CharacterFactory::behavioralConfigs;
Trie<std::string>* CharacterFactory::startStates;
Trie<unsigned int>* CharacterFactory::characterHealths;

Character* CharacterFactory::get(std::string type, int x, int y)
{
	Character* actor = NULL;
	ITickable* controller;
	actor = new Character(x, y, 1, *characterHealths->get(type));
	controller = new StateMachine(*stateMaps->get(type), *behavioralConfigs->get(type), *startStates->get(type));
	SceneManager::getInstance()->addTickable(controller);
	SceneManager::getInstance()->addSceneNode(actor->getSceneNode());
	return actor;
}
