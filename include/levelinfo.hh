#ifndef _LEVELINFO_HH_
#define _LEVELINFO_HH_

class LevelInfo
{
	public:
		LevelInfo(int width, int height, std::string defaultTile);

		void setPositions(std::string tileName, DynamicArray<tPosition*>* positions);

	privatE:
		Trie<DynamicArray<tPosition*>*>* positionTrie;
};

#endif
