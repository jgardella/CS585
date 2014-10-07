#include "debug.hh"
#include "istate.hh"
#include "iactor.hh"
#include "trie.hh"
#include "statemachine.hh"
#include "dispatcher.hh"


class FleeState : public IState
{
	public:
		FleeState(IActor* actor, Trie<float>* behavior) : IState(actor, behavior) 
		{
			timeCounter = 0;
	       	}

		void tick(float dt)
		{
			timeCounter += dt;
			if(timeCounter >= 5)
			{
				Debug::getInstance()->log("GAMEPLAY", "Actor is in FleeState and is fleeing.");
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
			health = 100;
		}

		int getHealth()
		{
			return health;
		}

	private:	
		int health;
};

class IdleState : public IState
{
	public:
		IdleState(IActor* actor, Trie<float>* behavior) : IState(actor, behavior) { }
		void tick(float dt)
	       	{
	       		if(((Actor*)actor)->getHealth() < *behavioralConfig->get("fleeAtHealth"))
			{

			}
		}
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
			states->add("active", new FleeState(actor, behaviors));
			stateMachine = new StateMachine(states, behaviors, "idle");
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
	return 0;
}
