#ifndef _CHARACTERFACTORY_HH_
#define _CHARACTERFACTORY_HH_

#include "scenemanager.hh"
#include "character.hh"
#include "trie.hh"
#include "istate.hh"
#include "statemachine.hh"

class CharacterFactory
{
	public:

		// Creates a new character of the given type and places it at the given coordinates in the world. Returns a reference to the actor.
		// Parameters:
		// std::string type - the type of the actor
		// int x - the x coordinate at which to instantiate the actor
		// int y - the y coordinate at which to instantiate the actor
		static Character* get(std::string type, int x, int y);
	
	private:
		static Trie<Trie<IState*>*>* stateMaps;
		static Trie<Trie<float>*>* behavioralConfigs;
		static Trie<std::string>* startStates;
		static Trie<unsigned int>* characterHealths;
};

#endif
