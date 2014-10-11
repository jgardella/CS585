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
	       	}

		void tick(float dt)
		{
			Debug::getInstance()->log("GAMEPLAY", "Actor is in FleeState and is fleeing.");
			dispatcher->tick(1);
		}
};

class TestActor : public IActor
{
	public:
		TestActor() : IActor(true, "ACTOR") 
		{
			health = 100;
		}

		int getHealth()
		{
			return health;
		}

		void simulateAttack(int lostHealth)
		{
			health -= lostHealth;
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
			dispatcher->tick(1);
			Debug::getInstance()->log("GAMEPLAY", "Actor is in idle state.");
	       		if(((TestActor*)actor)->getHealth() < *behavioralConfig->get("fleeAtHealth"))
			{
				dispatcher->dispatch(new StateEvent("flee"));
			}
		}
};

class Controller : public ITickable
{
	public:
		Controller(TestActor* actor)
		{
			this->actor = actor;
			Trie<float>* behaviors = new Trie<float>();
			behaviors->add("fleeAtHealth", 25);
			Trie<IState*>* states = new Trie<IState*>();
			IdleState* idle = new IdleState(actor, behaviors);
			FleeState* flee = new FleeState(actor, behaviors);
			states->add("idle", idle);
			states->add("flee", flee);
			stateMachine = new StateMachine(states, behaviors, "idle");
			idle->addListener("state", stateMachine->getListener());
			flee->addListener("state", stateMachine->getListener());
		}
		
		void tick(float dt)
		{
			stateMachine->tick(dt);
		}
	private:
		StateMachine* stateMachine;
		TestActor* actor;
};

void debugInit()
{
	#ifndef DEBUG
	Debug::getInstance()->setDebugStatus(false);
	#else
	Debug::getInstance()->setDebugStatus(true);
	Debug::getInstance()->addChannel("LISTENER");
	Debug::getInstance()->addChannel("DISPATCHER");
	Debug::getInstance()->addChannel("STATEMACHINE");
	Debug::getInstance()->unmuteAll();
	#endif
}

int main()
{
	debugInit();
	TestActor* actor = new TestActor();
	Controller* controller = new Controller(actor);
	controller->tick(1);
	actor->simulateAttack(80);
	controller->tick(1);
	controller->tick(1);	
	controller->tick(1);	
	controller->tick(1);	
	controller->tick(1);	
	controller->tick(1);	
	return 0;
}
