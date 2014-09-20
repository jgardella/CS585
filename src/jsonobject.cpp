#include "jsonobject.hh"

JSONObject::JSONObject(Trie<*JSONItem>* trie)
{
	this->trie = trie;
	this->type = OBJECT;
}

Trie<*JSONItem>* getTrie()
{
	return trie;
}
