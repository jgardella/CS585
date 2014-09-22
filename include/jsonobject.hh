#ifndef _JSONOBJECT_HH_
#define _JSONOBJECT_HH_

#include "jsonitem.hh"
#include "trie.hh"

// Wrapper class for JSONObject, continaing a trie.
class JSONObject : public JSONItem
{
	public:
		// Constructs a JSONObject containing the given trie.
		// Parameters:
		// Trie<JSONItem*>* trie - the trie to store in the JSONObject
		JSONObject(Trie<JSONItem*>* trie);
		~JSONObject();
		Trie<JSONItem*>* getTrie();
	private:
		Trie<JSONItem*>* trie;
};

#endif
