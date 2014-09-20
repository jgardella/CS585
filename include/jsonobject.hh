#ifndef _JSONOBJECT_HH_
#define _JSONOBJECT_HH_

#include "jsonitem.hh"
#include "trie.hh"

class JSONObject : public JSONItem
{
	public:
		// Constructs a JSONObject containing the given trie.
		JSONObject(Trie<*JSONItem>* trie);
		~JSONObject();
		Trie<*JSONItem>* getTrie();
	private:
		Trie<*JSONItem>* trie;
};

#endif
