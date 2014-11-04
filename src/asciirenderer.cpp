#include "asciirenderer.hh"

ASCIIRenderer::ASCIIRenderer(int x, int y, int fps) : IRenderer(x, y, fps)
{
	initscr();
	start_color();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(FALSE);
	renderInfos = new Trie<tRenderInfo*>();
}

void ASCIIRenderer::render()
{
	unsigned int i, j, k;
	DynamicArray<SceneNode*>* nodes;
	IActor* actor;
	tRenderInfo* renderInfo;
	getmaxyx(stdscr, maxY, maxX);
	clear();
	for(i = renderX; i < renderX + maxX; i++)
	{
		for(j = renderY; j < renderY + maxY; j++)
		{
			if(i < (unsigned int)LevelManager::getInstance()->getWorldWidth() && j < (unsigned int)LevelManager::getInstance()->getWorldHeight())
			{
				nodes = SceneManager::getInstance()->getColliders(i, j);
				if(nodes->length() == 0)
				{
					renderInfo = *renderInfos->get(LevelManager::getInstance()->getDefaultTile());
				}
				else
				{
					actor = (*nodes->get(0))->getActor();
					for(k = 1; k < nodes->length(); k++)
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
				attron(COLOR_PAIR(renderInfo->colorPair));
				mvprintw(j - renderY, i - renderX, renderInfo->character.c_str());
			}
		}
	}
	refresh();
}

void ASCIIRenderer::addRenderInfo(std::string type, tRenderInfo* info)
{
	renderInfos->add(type, info);
}

void ASCIIRenderer::moveX(int dx)
{
	if(dx < 0 && renderX > 0)
	{
		renderX += dx;
	}
	else if((unsigned int)renderX < LevelManager::getInstance()->getWorldWidth() - maxX)
	{
		renderX += dx;
	}
}

void ASCIIRenderer::moveY(int dy)
{
	if(dy < 0 && renderY > 0)
	{
		renderY += dy;
	}
	else if((unsigned int)renderY < LevelManager::getInstance()->getWorldHeight() - maxY)
	{
		renderY += dy;
	}
}
