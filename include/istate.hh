#ifndef _ISTATE_HH_
#define _ISTATE_HH_

#include "itickable.hh"
#include "trie.hh"
#include "iactor.hh"
#include "dispatcher.hh"

class IState : public ITickable
{
	protected:
		IState(IActor* act, Trie<float>* config) : actor(act), behavioralConfig(config) 
		{
			dispatcher = new Dispatcher();
		}
		IActor* actor;
		Trie<float>* behavioralConfig;
		Dispatcher* dispatcher;
};

#endif
