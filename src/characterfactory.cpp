#include "characterfactory.hh"

Trie<tCharacterInfo*>* CharacterFactory::characterInfos;

Character* CharacterFactory::get(std::string type, int x, int y)
{
	Character* actor = NULL;
	ITickable* controller;
	tCharacterInfo* info = *characterInfos->get(type);
	actor = new Character(x, y, 1, info->health);
	controller = new CharacterController(actor, info->stateMap, info->behavioralConfig, info->startState);
	SceneManager::getInstance()->addTickable(controller);
	SceneManager::getInstance()->addSceneNode(actor->getSceneNode());
	return actor;
}

void CharacterFactory::addCharacterInfo(std::string name, tCharacterInfo* info)
{
	characterInfos->add(name, info);
}
