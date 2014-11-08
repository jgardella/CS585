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
		// Adds a listener to the state.
		// Parameters:
		// std::string type - the type of listener
		// IListenerCallback* listener - pointer to the listener's callback
		void addListener(std::string type, IListenerCallback* listener);
		
		void setActor(IActor* actor);

		// Congifures the state every time it is transitioned to.
		void preStateStart();

	protected:

		// Constructs a state with the given actor and config.
		// Parameters:
		// IActor* act - pointer to the statemachine's actor
		// Trie<float>* config - pointer to the actor's behavioral config
		IState(IActor* act); 
		IActor* actor;
		Dispatcher* dispatcher;
		bool active;
};

#endif
