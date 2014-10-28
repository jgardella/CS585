#include "levelinfo.hh"

sLevelInfo::sLevelInfo(int w, int h, std::string defaultT) : width(w), height(h), defaultTile(defaultT)
{
	positionTrie = new Trie<DynamicArray<tPosition*>*>();
}

void sLevelInfo::setPositions(std::string tileName, DynamicArray<tPosition*>* positions)
{
	positionTrie->add(tileName, positions);
}
