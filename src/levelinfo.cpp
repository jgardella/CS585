#include "levelinfo.hh"

LevelInfo::LevelInfo(int w, int h, std::string defaultT) : width(w), height(h), defaultTile(defaultT)
{
	positionTrie = new Trie<DynamicArray<tPosition*>*>();
}

void LevelInfo::setPositions(std::string tileName, DynamicArray<tPosition*>* positions)
{
	positionTrie->add(tileName, positions);
}
