#ifndef _CHARACTERINFO_HH_
#define _CHARACTERINFO_HH_

typedef struct sCharacterInfo
{
	std::string type;
	Trie<IState*>* stateMap;
	Trie<double>* behavioralConfig;
	std::string startState;
	unsigned int health;
} tCharacterInfo;

#endif
