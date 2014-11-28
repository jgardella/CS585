#ifndef _STATEMACHINE_HH_
#define _STATEMACHINE_HH_

#include "dynamicarray.hh"
#include "trie.hh"
#include "ievent.hh"
#include "stateevent.hh"
#include "itickable.hh"
#include "ilistenercallback.hh"
#include "istate.hh"
#include "debug.hh"

// StateMachine class used as implementation of controller.
class StateMachine : public ITickable
{

	public:
		// Constructs a state machine with the given state map, behavioural config, and starting state.
		// Parameters:
		// Trie<IState*>* map - a state map representing the mapping from string name to state implementation
		// Trie<float>* config - mapping from string to float representing behavioral values of the state machine
		// std::string startState - the name of the state to start the machine in
		StateMachine(Trie<IState*>* map, Trie<double>* config, std::string startState);
		
		virtual ~StateMachine();

		// Ticks the state machine, executing the current state.
		// Parameters:
		// float dt - change in time since last tick
		void tick(float dt);	
		
		// Returns a reference to the state machine's listener.
		IListenerCallback* getListener();
		
		// Updates the current state to the state given by the state map for the specified state name.
		// Parameters:
		// std::string stateString - the name of the state to update to
		void updateState(std::string stateString);

	private:
		Trie<IState*>* stateMap;
		Trie<double>* behavioralConfig;
		IState* currentState;

		// Listener callback for state transitions	
		class OnStateTransition : public IListenerCallback
		{
			public:
				OnStateTransition() { }
				void setInstance(StateMachine* machine)
				{
					stateMachine = machine;
				}
				
				// Updates the machine's state to the state contained in the StateEvent.		
				virtual void execute(IEvent* event)
				{
					DEBUG_LOG("STATEMACHINE", "State transition callback executed.");
					if(event->getType().compare("state") == 0)
					{
						StateEvent* stateEvent = (StateEvent*) event;
						DEBUG_LOG("STATEMACHINE", "State transition callback changing state to " + stateEvent->getState());
						stateMachine->updateState(stateEvent->getState());
					}
				}
				

			private:
				StateMachine* stateMachine;
		} onStateTransition; 
};

#endif
