#ifndef _TRIE_HH_
#define _TRIE_HH_

#include "../dynamicarray/dynamicarray.hh"
#include <string>
#include "debug.hh"

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

		void add(std::string key, Value value)
		{
			addValue(key, value);
		}

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
			if(key.compare("") != 0) // base case, if key is empty string, final node has been reached. return value.
			{
				std::string firstLetter = key.substr(0, 1);
				Debug::log("TRIE", "First letter of key is " + firstLetter);
				// look through edges to find match with first letter.
				for(i = 0; i < children->length(); i++)
				{
					Trie* node = children->get(i);
					if(node->key.compare(firstLetter) == 0)
					{
						Debug::log("TRIE", "Match found with key " + node->key);
						return node->findValue(key.substr(1, std::string::npos)); // recursive call to follow edge to next node.
					}
				}
				// key did not match any of nodes edges, so it is not in trie.
			}
			return value;
		}

		void addValue(std::string key, Value newValue)
		{
			Debug::log("TRIE", "addValue method enter with key " + key);
			int i;
			std::string firstLetter;
			if(key.compare("") != 0)
			{
				firstLetter = key.substr(0, 1);
				Debug::log("TRIE", "First letter is " + firstLetter);
				for(i = 0; i < children->length(); i++)
				{
					Trie* node = children->get(i);
					if(node->key.compare(firstLetter) == 0)
					{
						Debug::log("TRIE", "Match found with key " + node->key);
						node->addValue(key.substr(1, std::string::npos), newValue);
						return;
					}
				}
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
