#ifndef _ASCIIRENDERER_HH_
#define _ASCIIRENDERER_HH_

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
		
		void render();
		void addRenderInfo(std::string type, tRenderInfo* info);
	private:
		Trie<tRenderInfo*>* renderInfos;
};

#endif
