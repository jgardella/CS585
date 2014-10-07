#ifndef _ISTATE_HH_
#define _ISTATE_HH_

#include "itickable.hh"
#include "trie.hh"
#include "iactor.hh"
#include "dispatcher.hh"
#include "ilistenercallback.hh"

// Interface for a state in a state machine. All states contain a reference to their actor and their behavioral config, as well as a dispatcher to dispatch state changes to the state machine.
class IState : public ITickable
{
	public:
		void addListener(std::string type, IListenerCallback* listener)
		{
			dispatcher->addListener(type, listener);
		}

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
