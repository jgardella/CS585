#ifndef _WORLDSTATE_HH_
#define _WORLDSTATE_HH_

#include "istate.hh"
#include "asciirenderer.hh"
#include "ilistenercallback.hh"
#include "ievent.hh"
#include "inputevent.hh"
#include "inputmanager.hh"

class WorldState : public IState
{
	public:
		virtual void tick(float dt) = 0;
		virtual void parseInput(int key) = 0;
	protected:
		WorldState(ASCIIRenderer* renderer);
		ASCIIRenderer* renderer;
		
		class OnInputEvent : public IListenerCallback
		{
			public:
				OnInputEvent() 
				{
					InputManager::getInstance()->addListener(this);
				}

				void setController(WorldState* controller)
				{
					this->controller = controller;
				}

				virtual void execute(IEvent* event)
				{
					DEBUG_LOG("WORLDSTATE", "User controller received input event.");
					if(event->getType().compare("input") == 0)
					{
						InputEvent* inputEvent = (InputEvent*)event;
						controller->parseInput(inputEvent->getInput());
					}
				}

			private:
				WorldState* controller;
		} inputListener;
};

#endif
