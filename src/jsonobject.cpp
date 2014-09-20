#include "jsonobject.hh"

JSONObject::JSONObject(Trie<*JSONItem>* trie)
{
	this->trie = trie;
	this->type = OBJECT;
}

JSONObject::~JSONObject()
{
	delete trie;
}

Trie<*JSONItem>* JSONObject::getTrie()
{
	return trie;
}
