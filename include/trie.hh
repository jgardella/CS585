#ifndef _TRIE_HH_
#define _TRIE_HH_

#include "dynamicarray.hh"
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
			Debug::log("TRIE", "Constructing node with no value");
			children = new Trie*[26]();
		}
		
		// Destructor
		~Trie()
		{
			// no need to manually call destructor of child tries, as the dynamic array's destructor will automatically call them.
			delete children;
		}

		// Adds a new value to the trie with the given key.
		// Parameters:
		// string key - the key to use to store the value
		// Value value - the value to store
		void add(std::string key, Value newValue)
		{
			Debug::log("TRIE", "add method enter with key " + key);
			std::string firstLetter;
			Trie *newTrie;
			if(key.compare("") != 0) // base case, if key is empty string, final node has been reached. set its value to the given value.
			{
				firstLetter = key.at(0);
				Debug::log("TRIE", "First letter is " + firstLetter);
				if(children[key.at(0) - 'a'] == 0)
				{
					Debug::log("TRIE", "Creating new node with key " + firstLetter);
					newTrie = new Trie();
					children[key.at(0) - 'a'] = newTrie;
				}
				children[key.at(0) - 'a']->add(key.substr(1, std::string::npos), newValue);	
			}
			else
			{
				Debug::log("TRIE", "Setting value.");
				value = newValue;
			}
		}

		// Returns the value in the array with the given key.
		// Parameters:
		// string key - the key to search for, must be a valid key which was previously added to the array
		Value get(std::string key)
		{
			Debug::log("TRIE", "get method entered with key " + key);
			std::string firstLetter;
			if(key.compare("") != 0) // base case, if key is empty string, final node has been reached. return value.
			{
				firstLetter = key.substr(0, 1);
				Debug::log("TRIE", "First letter of key is " + firstLetter);
				return children[key.at(0) - 'a']->get(key.substr(1, std::string::npos));
			}
			Debug::log("TRIE", "Returning value");
			return value;
		}
		
	private:
		Trie **children;
		Value value;
		
		// Constructs a node with the given value and key.
		Trie(Value value)
		{
			Debug::log("TRIE", "Constructing node with value.");
			children = new Trie*[26]();
			this->value = value;
		}

};

#endif
