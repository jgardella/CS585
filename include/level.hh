#ifndef _LEVEL_HH_
#define _LEVEL_HH_

#include "levelinfo.hh"
#include "fixedgrid.hh"
#include "scenemanager.hh"
#include "tilefactory.hh"
#include "statemachine.hh"
#include "building.hh"
#include "charactercontroller.hh"
#include "ilistenercallback.hh"
#include "ievent.hh"
#include "deathevent.hh"

class Level : public ITickable
{
	public:
		// Constructs a level with a world of the given width and height.
		// Parameters:
		// int width - the width of the world
		// int height - the height of the world
		Level(tLevelInfo level);
		
		void tick(float dt);
		
		int getWorldWidth();
		int getWorldHeight();
		Building* getHome(unsigned int teamNum);
		std::string getDefaultTile();
		CharacterController* getControllerForCharacter(unsigned int id);
		void removeControllerForCharacter(unsigned int id);
		void addControllerForCharacter(CharacterController* controller);
		void addHome(Building* building);
		IListenerCallback* getListener();
		unsigned int getPlayerGold();
		void changePlayerGold(int amount);
	private:
		int width;
		int height;
		unsigned int playerGold;
		std::string defaultTile;
		DynamicArray<Building*>* teamHomes;
		DynamicArray<CharacterController*>* characterControllers;
		
		void processDeathEvent(DeathEvent* event);

		// Listener callback for deaths
		class OnDeathEvent : public IListenerCallback
		{
			public:
				OnDeathEvent() { }
				void setInstance(Level* level)
				{
					this->level = level;
				}
				
				// Transfers gold and removes the controller for the dead actor.		
				virtual void execute(IEvent* event)
				{
					DEBUG_LOG("LEVEL", "Death event callback executed.");
					if(event->getType().compare("death") == 0)
					{
						DeathEvent* deathEvent = (DeathEvent*) event;
						level->processDeathEvent(deathEvent);
					}
				}
				

			private:
				Level* level;
		} onDeathEvent; 
};

#endif
