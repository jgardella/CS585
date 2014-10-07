#include "debug.hh"
#include "istate.hh"
#include "iactor.hh"
#include "trie.hh"
#include "statemachine.hh"
#include "dispatcher.hh"

class IdleState : public IState
{
	public:
		IdleState(IActor* actor, Trie<float>* behavior) : IState(actor, behavior) { }
		void tick(float dt) { }
};

class ActiveState : public IState
{
	public:
		ActiveState(IActor* actor, Trie<float>* behavior) : IState(actor, behavior) 
		{
			timeCounter = 0;
	       	}

		void tick(float dt)
		{
			timeCounter += dt;
			if(timeCounter >= 5)
			{
				Debug::getInstance()->log("GAMEPLAY", "Actor is in ActiveState and printing every 5 seconds.");
				timeCounter = 0;
			}
		}
	private:
		float timeCounter;
};

class Actor : public IActor
{
	public:
		Actor() : IActor(true, "ACTOR") 
		{
			events = new Dispatcher();
		}
		
		void simulateEventTrigger()
		{
			events->dispatch(new StateEvent("active"));
			events->tick(5);
		}

		Dispatcher* events;
};

class Controller : public ITickable
{
	public:
		Controller(Actor* actor)
		{
			this->actor = actor;
			Trie<float>* behaviors = new Trie<float>();
			Trie<IState*>* states = new Trie<IState*>();
			states->add("idle", new IdleState(actor, behaviors));
			states->add("active", new ActiveState(actor, behaviors));
			stateMachine = new StateMachine(states, behaviors, "idle");
			actor->events->addListener("state", stateMachine->getListener());
		}
		
		void tick(float dt)
		{
			stateMachine->tick(dt);
		}
	private:
		StateMachine* stateMachine;
		Actor* actor;
};

void debugInit()
{
	#ifndef DEBUG
	Debug::getInstance()->setDebugStatus(false);
	#else
	Debug::getInstance()->setDebugStatus(true);
	Debug::getInstance()->addChannel("LISTENER");
	Debug::getInstance()->addChannel("DISPATCHER");
	Debug::getInstance()->unmuteAll();
	#endif
}

int main()
{
	debugInit();
	Actor* actor = new Actor();
	Controller* controller = new Controller(actor);
	controller->tick(5);
	actor->simulateEventTrigger();
	controller->tick(5);	
	controller->tick(5);	
	controller->tick(5);	
	controller->tick(5);	
	return 0;
}
