#ifndef _TRIE_HH_
#define _TRIE_HH_

typedef struct sEdge
{
	Node *nextNode;
	std::string key;
}

template <class Value>
class Node
{
	public:
		// Constructs a node with the given value.
		Node(Value value)
		{
			edgesToChildren = new DynamicArray<Edge>();
			this->value = value;
		}
		
		// Constructs a node with no value.
		Node()
		{
			edgesToChildren = new DynamicArray<Edge>();
			value = NULL;
		}
		
		Value getValue()
		{
			return *value;
		}

		// Adds a new edge to this node.
		// Parameters:
		// Edge newEdge - the edge to be added
		void addEdge(sEdge newEdge)
		{
			edgesToChildren->pushBack(newEdge);
		}

		// Follows the edge specified by the first character of key and recursively returns a pointer to the value at the end of the key, or returns pointer to NULL if no children match key.
		// Parameters:
		// std::string key - the full key to search for from this node.
		// Returns a pointer to the value of the given key in the trie, or a pointer to NULL if the key is not in the trie.
		Value* followEdgeWithKey(std::string key)
		{
			if(key.compareTo("") != 0) // base case, if key is empty string, final node has been reached. return value.
			{
				std::string firstLetter = key.substr(0, 1);
				int i;
				// look through edges to find match with first letter.
				for(i = 0; i < edgesToChildren->length(); i++)
				{
					if(sEdge.key.compareTo(firstLetter) == 0)
					{
						return followEdgeWithKey(key.substr(1, std::string::npos)); // recursive call to follow edge to next node.
					}
				}
				return NULL; // key did not match any of nodes edges, so it is not in trie.
			}
			return value;
		}

	private:
		DynamicArray<sEdge> *edgesToChildren;
		Value *value;
}



template <class Value>
class Trie
{
	public:
		
	private:
		tNode root;
}

#endif
