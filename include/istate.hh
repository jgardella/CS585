#ifndef _ISTATE_HH_
#define _ISTATE_HH_

#include "itickable.hh"
#include "trie.hh"
#include "iactor.hh"

class IState : public ITickable
{
	protected:
		IState(IActor* act, Trie<float>* config) : actor(act), behavioralConfig(config) {}
		IActor* actor;
		Trie<float>* behavioralConfig;
};

#endif
