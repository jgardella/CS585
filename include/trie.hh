#ifndef _TRIE_HH_
#define _TRIE_HH_

#include "dynamicarray.hh"
#include <string>
#include "debug.hh"

// Trie data structure implementation.
template <class T>
class Trie
{

	template <class Value>
	class Node
	{
		public:
			// Constructs a node with no value or key (used for making root).
			Node()
			{
				DEBUG_LOG("TRIE", "Constructing node with no value");
				children = new Node*[26]();
			}
			
			// Destructor
			~Node()
			{
				// delete all Tries in children
				unsigned int i;
				for(i = 0; i < 26; i++)
				{
					if(children[i] != NULL)
					{
						delete children[i];
					}
				}
				delete [] children;
			}

			// Adds a new value to the trie with the given key.
			// Parameters:
			// string key - the key to use to store the value
			// Value value - the value to store
			void add(std::string key, Value newValue)
			{
				DEBUG_LOG("TRIE", "add method enter with key " + key);
				std::string firstLetter;
				Node *newTrie;
				if(key.compare("") != 0) // base case, if key is empty string, final node has been reached. set its value to the given value.
				{
					firstLetter = key.at(0);
					DEBUG_LOG("TRIE", "First letter is " + firstLetter);
					if(children[key.at(0) - 'a'] == 0)
					{
						DEBUG_LOG("TRIE", "Creating new node with key " + firstLetter);
						newTrie = new Node();
						children[key.at(0) - 'a'] = newTrie;
					}
					children[key.at(0) - 'a']->add(key.substr(1, std::string::npos), newValue);	
				}
				else
				{
					DEBUG_LOG("TRIE", "Setting value.");
					value = newValue;
				}
			}

			// Returns the value in the array with the given key.
			// Parameters:
			// string key - the key to search for, must be a valid key which was previously added to the array
			Value* get(std::string key)
			{
				DEBUG_LOG("TRIE", "get method entered with key " + key);
				if(key.compare("") != 0) // base case, if key is empty string, final node has been reached. return value.
				{
					if(children[key.at(0) - 'a'] != NULL)
					{
						return children[key.at(0) - 'a']->get(key.substr(1, std::string::npos));
					}
					else
					{
						return NULL;
					}
				}
				DEBUG_LOG("TRIE", "Returning value");
				return &value;
			}
			
		private:
			Node **children;
			Value value;
			
			// Constructs a node with the given value and key.
			Node(Value value)
			{
				DEBUG_LOG("TRIE", "Constructing node with value.");
				children = new Node*[26]();
				this->value = value;
			}
	};
	
	public:
		Trie()
		{
			root = new Node<T>();
			keys = new DynamicArray<std::string>();
		}

		// Adds a new value to the trie with the given key.
		// Parameters:
		// string key - the key to use to store the value
		// Value value - the value to store
		void add(std::string key, T newValue)
		{
			root->add(key, newValue);
			keys->pushBack(key);
		}

		// Returns the value in the array with the given key.
		// Parameters:
		// string key - the key to search for, must be a valid key which was previously added to the array
		T* get(std::string key)
		{
			return root->get(key);
		}

	private:
		Node<T>* root;
		DynamicArray<std::string>* keys;
};

#endif
