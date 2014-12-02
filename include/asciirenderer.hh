#ifndef _ASCIIRENDERER_HH_
#define _ASCIIRENDERER_HH_

#include "menumanager.hh"
#include "irenderer.hh"
#include "levelmanager.hh"
#include "scenemanager.hh"
#include "dynamicarray.hh"
#include "scenenode.hh"
#include "renderinfo.hh"
#include <ncurses.h>

class ASCIIRenderer : public IRenderer
{
	public:
		ASCIIRenderer(int x, int y, int fps);
		
		void moveX(int x);

		void moveY(int y);
		
		void moveCursorX(int x);

		void moveCursorY(int y);
		
		void setInspectOutput(bool newValue);
		
		void lockInspectOutput();

		void unlockInspectOutput();
		
		IActor* getLockedActor();
		
		int getCursorWorldX();

		int getCursorWorldY();
		
		void drawMenu();

		void render();
		void addRenderInfo(std::string type, tRenderInfo* info);
		
		void drawPlayerGold();	
		void drawWorldState();
		void drawAlert();
		void drawInspectInfo(IActor* actorUnderCursor);
		void setWorldState(std::string state);

	private:
		Trie<tRenderInfo*>* renderInfos;
		unsigned int maxX, maxY;
		unsigned int cursorX, cursorY;
		bool showInspectInfo;
		IActor* inspectActor;
		std::string state;
};

#endif
