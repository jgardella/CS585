#include "asciirenderer.hh"

ASCIIRenderer::ASCIIRenderer(int x, int y, int fps) : IRenderer(x, y, fps)
{
	initscr();
	noecho();
	curs_set(false);
	renderInfos = new Trie<tRenderInfo*>();
}

void ASCIIRenderer::render()
{
	unsigned int i, j, k;
	DynamicArray<SceneNode*>* nodes;
	IActor* actor;
	tRenderInfo* renderInfo;
	unsigned int maxX = 0, maxY = 0;
	getmaxyx(stdscr, maxY, maxX);
	clear();
	for(i = renderX; i < renderX + maxX; i++)
	{
		for(j = renderY; j < renderY + maxY; j++)
		{
			nodes = SceneManager::getInstance()->getColliders(i, j);
			if(nodes->length() == 0)
			{
				renderInfo = *renderInfos->get(LevelManager::getInstance()->getDefaultTile());
			}
			else
			{
				for(k = 0; k < nodes->length(); k++)
				{
					if((*nodes->get(k))->getActor()->getCollisionLayer() > actor->getCollisionLayer())
					{
						actor = (*nodes->get(k))->getActor();
					}
				}
				if(actor->getClass().compare("CHARACTER") == 0)
				{
					renderInfo = *renderInfos->get(((Character*)actor)->getType());
				}
				else if(actor->getClass().compare("TILE") == 0)
				{
					renderInfo = *renderInfos->get(((Tile*)actor)->getType());
				}
			}
			mvprintw(i, j, renderInfo->character.c_str());
		}
	}
	refresh();
}

void ASCIIRenderer::addRenderInfo(std::string type, tRenderInfo* info)
{
	renderInfos->add(type, info);
}
