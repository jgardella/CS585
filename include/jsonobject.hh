#ifndef _JSONOBJECT_HH_
#define _JSONOBJECT_HH_

class JSONObject
{
	public:
		// Constructs a JSONObject containing the given trie.
		JSONObject(Trie<*JSONItem> trie);
		Trie<*JSONItem> getHashMap();
	private:
		Trie<*JSONItem> trie;
};

#endif
