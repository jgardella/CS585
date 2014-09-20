#include "jsonobject.hh"

JSONObject::JSONObject(Trie<JSONItem*>* trie) : JSONItem(OBJECT)
{
	this->trie = trie;
}

JSONObject::~JSONObject()
{
	delete trie;
}

Trie<JSONItem*>* JSONObject::getTrie()
{
	return trie;
}
