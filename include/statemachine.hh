#include "dynamicarray.hh"
#include "trie.hh"
#include "ievent.hh"
#include "itickable.hh"
#include "ilistenercallback.hh"

class StateMachine : public ITickable
{

	class OnSceneTransition : public IListenerCallback
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
			
			void tick(float dt);	

		private:
			const StateMachine* stateMachine;
	} sceneTransitionListener(this);

	public:
		StateMachine(Trie<State>* stateMap, Trie<float>* behavioralConfig);

	private:
		State currentState;
		Trie<State>* stateMap;
		Trie<float>* behavioralConfig;
};
