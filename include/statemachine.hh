#ifndef _STATEMACHINE_HH_
#define _STATEMACHINE_HH_

#include "dynamicarray.hh"
#include "trie.hh"
#include "ievent.hh"
#include "itickable.hh"
#include "ilistenercallback.hh"
#include "istate.hh"

class StateMachine : public ITickable
{
	// Listener callback for state transitions
	class OnStateTransition : public IListenerCallback
	{
		public:
			OnStateTransition() { }
			OnMonsterKilled(const StateMachine* machine): stateMachine(machine){ }
			virtual void execute(IEvent* event)
			{
				if(event->getType().compare("state") == 0)
				{
					StateEvent* stateEvent = (*StateEvent) event;
					currentState = stateMap->get(stateEvent->getState());
				}
			}
			

		private:
			const StateMachine* stateMachine;
	} sceneTransitionListener(this);

	public:
		StateMachine(Trie<State>* map, Trie<float>* config) : stateMap(map), behavioralConfig(config), currentState(map->get("idle"));
		void tick(float dt);	

	private:
		IState* currentState;
		Trie<IState*>* stateMap;
		Trie<float>* behavioralConfig;
};

#endif
