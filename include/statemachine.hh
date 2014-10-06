#ifndef _STATEMACHINE_HH_
#define _STATEMACHINE_HH_

#include "dynamicarray.hh"
#include "trie.hh"
#include "ievent.hh"
#include "stateevent.hh"
#include "itickable.hh"
#include "ilistenercallback.hh"
#include "istate.hh"

class StateMachine : public ITickable
{

	public:
		StateMachine(Trie<IState*>* map, Trie<float>* config, std::string startState);
		void tick(float dt);	

		IListenerCallback* getListener();

	private:
		Trie<IState*>* stateMap;
		Trie<float>* behavioralConfig;
		IState* currentState;
		
		void updateState(std::string stateString);

		// Listener callback for state transitions	
		class OnStateTransition : public IListenerCallback
		{
			public:
				OnStateTransition() { }
				void setInstance(StateMachine* machine)
				{
					stateMachine = machine;
				}
				
				virtual void execute(IEvent* event)
				{
					if(event->getType().compare("state") == 0)
					{
						StateEvent* stateEvent = (StateEvent*) event;
						stateMachine->updateState(stateEvent->getState());
					}
				}
				

			private:
				StateMachine* stateMachine;
		} onStateTransition; 
};

#endif
