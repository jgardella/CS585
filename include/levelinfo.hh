#ifndef _LEVELINFO_HH_
#define _LEVELINFO_HH_

#include "trie.hh"
#include "dynamicarray.hh"
#include "sposition.hh"

class LevelInfo
{
	public:
		// Constructs a new level info object.
		// Parameters:
		// int width - width of level
		// int height - height of level
		// std::string defaultTile - default tile for level
		LevelInfo(int width, int height, std::string defaultTile);
		
		// Adds the given dynamic array of positions to the level info with the specified name.
		// Parameters:
		// std::string tileName - the name of the actor
		// DynamicArray<tPosition*>* positions - the posititions at which to place the actor
		void setPositions(std::string tileName, DynamicArray<tPosition*>* positions);

	private:
		Trie<DynamicArray<tPosition*>*>* positionTrie;
		std::string defaultTile;
		int width, height;
};

#endif
