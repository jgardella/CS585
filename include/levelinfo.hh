#ifndef _LEVELINFO_HH_
#define _LEVELINFO_HH_

#include "trie.hh"
#include "dynamicarray.hh"
#include "sposition.hh"

typedef struct sLevelInfo
{
		// Constructs a new level info object.
		// Parameters:
		// int width - width of level
		// int height - height of level
		// std::string defaultTile - default tile for level
		sLevelInfo(int width, int height, std::string defaultTile, unsigned int initialGold);
		
		// Adds the given dynamic array of positions to the level info with the specified name.
		// Parameters:
		// std::string tileName - the name of the actor
		// DynamicArray<tPosition*>* positions - the posititions at which to place the actor
		void setPositions(std::string tileName, DynamicArray<tPosition*>* positions);

		Trie<DynamicArray<tPosition*>*>* positionTrie;
		int width, height;
		std::string defaultTile;
		unsigned int initialGold;
} tLevelInfo;

#endif
