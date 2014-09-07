#ifndef _TRIE_HH_
#define _TRIE_HH_

#include "../dynamicarray/dynamicarray.hh"
#include <string>
#include "debug.hh"

// Trie data structure implementation.
template <class Value>
class Trie
{
	public:
		// Constructs a node with no value or key (used for making root).
		Trie()
		{
			Debug::getInstance()->addChannel("TRIE");
			Debug::log("TRIE", "Constructing node with no value or key");
			this->children = new DynamicArray<Trie*>();
		}

		// Adds a new value to the trie with the given key.
		// Parameters:
		// string key - the key to use to store the value
		// Value value - the value to store
		void add(std::string key, Value value)
		{
			addValue(key, value);
		}
		
		// Returns the value in the array with the given key.
		// Parameters:
		// string key - the key to search for, must be a valid key which was previously added to the array
		Value get(std::string key)
		{
			return findValue(key);
		}
		
	private:
		DynamicArray<Trie*> *children;
		Value value;
		std::string key; // the letter of the edge which had to be followed to reach this node
		
		// Constructs a node with the given value and key.
		Trie(Value value, std::string key)
		{
			this->children = new DynamicArray<Trie*>();
			this->value = value;
			this->key = key;
		}
		
		// Constructs a node with no value and the given key.
		Trie(std::string key)
		{
			this->children = new DynamicArray<Trie*>();
			this->key = key;
		}

		
		// Follows the edge specified by the first character of key and recursively returns a pointer to the value at the end of the key, or returns pointer to NULL if no children match key.
		// Parameters:
		// std::string key - the full key to search for from this node.
		// Returns a pointer to the value of the given key in the trie, or a pointer to NULL if the key is not in the trie.
		Value findValue(std::string key)
		{
			Debug::log("TRIE", "findValue method entered with key " + key);
			int i;
			std::string firstLetter;
			Trie* node;
			if(key.compare("") != 0) // base case, if key is empty string, final node has been reached. return value.
			{
				firstLetter = key.substr(0, 1);
				Debug::log("TRIE", "First letter of key is " + firstLetter);
				// look through edges to find match with first letter.
				for(i = 0; i < children->length(); i++)
				{
					node = children->get(i);
					if(node->key.compare(firstLetter) == 0)
					{
						Debug::log("TRIE", "Match found with key " + node->key);
						return node->findValue(key.substr(1, std::string::npos)); // recursive call to go to next node.
					}
				}
				// key did not match any of nodes edges, so it is not in trie.
			}
			return value;
		}
		
		// Recursively adds a new value to the trie using the given key.
		// Parameters:
		// string key - the key to use to store the value
		// Value newValue - the value to add to the trie
		void addValue(std::string key, Value newValue)
		{
			Debug::log("TRIE", "addValue method enter with key " + key);
			int i;
			std::string firstLetter;
			Trie* node;
			if(key.compare("") != 0) // base case, if key is empty string, final node has been reached. set its value to the given value.
			{
				firstLetter = key.substr(0, 1);
				Debug::log("TRIE", "First letter is " + firstLetter);
				// look through children to find a match with the first letter of the key
				for(i = 0; i < children->length(); i++)
				{
					node = children->get(i);
					if(node->key.compare(firstLetter) == 0)
					{
						Debug::log("TRIE", "Match found with key " + node->key);
						node->addValue(key.substr(1, std::string::npos), newValue); // recursive call to go to next node
						return;
					}
				}
				// branch did not exist and must be created.
				Debug::log("TRIE", "Creating new node with key " + firstLetter);
				Trie *newTrie = new Trie(firstLetter);
				children->pushBack(newTrie);
				newTrie->addValue(key.substr(1, std::string::npos), newValue);
			}
			else
			{
				value = newValue;
			}
		}
};

#endif
