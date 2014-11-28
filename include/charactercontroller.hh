#ifndef _CHARACTERCONTROLLER_HH_
#define _CHARACTERCONTROLLER_HH_

#include "character.hh"
#include "itickable.hh"
#include "trie.hh"
#include "istate.hh"
#include "statemachine.hh"
#include "ilistenercallback.hh"

class CharacterController : public ITickable
{
	public:
		CharacterController(Character* character, StateMachine* machine, unsigned int id);

		virtual ~CharacterController();

		void tick(float dt);
		
		unsigned int getID();

	protected:
		void updateState(std::string state);

	private:
		// Listener callback for actor events	
		class OnActorEvent : public IListenerCallback
		{
			public:
				OnActorEvent() { }
				void setInstance(CharacterController* controller)
				{
					this->controller = controller;
				}
				
				// Updates the machine's state to the state contained in the StateEvent.		
				virtual void execute(IEvent* event)
				{
					DEBUG_LOG("STATEMACHINE", "State transition callback executed.");
					if(event->getType().compare("state") == 0)
					{
						StateEvent* stateEvent = (StateEvent*) event;
						DEBUG_LOG("STATEMACHINE", "State transition callback changing state to " + stateEvent->getState());
						controller->updateState(stateEvent->getState());
					}
				}
				

			private:
				CharacterController* controller;
		} onActorEvent; 
		
		Character* character;
		StateMachine* machine;
		float timeCounter;
		unsigned int id;
};

#endif
