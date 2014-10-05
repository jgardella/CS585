#include "debug.hh"
#include "istate.hh"
#include "iactor.hh"
#include "trie.hh"
#include "statemachine.hh"

class IdleState : public IState
{
	public:
		IdleState(IActor* actor) : IState(actor) { }
		void tick(float dt) { }
};

class ActiveState : public IState
{
	public:
		ActiveState(IActor* actor) : IState(actor) 
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
		Actor() : IActor(true, "ACTOR") {}
};

class Controller : public ITickable
{
	public:
		Controller()
		{
			actor = new Actor();
			Trie<float>* behaviors = new Trie<float>();
			Trie<IState*>* states = new Trie<IState*>();
			states->add("idle", new IdleState(actor));
			states->add("active", new ActiveState(actor));
			stateMachine = new StateMachine(states, behaviors);
		}
		
		void tick(float dt)
		{
			stateMachine->tick(dt);
		}
	private:
		StateMachine* stateMachine;
		Actor* actor;
};

int main()
{
	return 0;
}
