#include "asciirenderer.hh"

ASCIIRenderer::ASCIIRenderer(int x, int y, int fps) : IRenderer(x, y, fps)
{
	initscr();
	start_color();
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	curs_set(FALSE);
	renderInfos = new Trie<tRenderInfo*>();
	cursorY = 0;
	cursorX = 0;
	move(cursorY, cursorX);
	showInspectInfo = false;
	inspectActor = NULL;
}

void ASCIIRenderer::render()
{
	unsigned int i, j, k;
	DynamicArray<SceneNode*>* nodes;
	IActor* actor = NULL;
	IActor* actorUnderCursor = NULL;
	tRenderInfo* renderInfo;
	getmaxyx(stdscr, maxY, maxX);
	clear();
	for(i = renderX; i < renderX + maxX; i++)
	{
		for(j = renderY; j < renderY + maxY; j++)
		{
			if(i < (unsigned int)LevelManager::getInstance()->getWorldWidth() && j < (unsigned int)LevelManager::getInstance()->getWorldHeight())
			{
				nodes = SceneManager::getInstance()->getColliders(i, j, false);
				if(nodes->length() == 0)
				{
					renderInfo = *renderInfos->get(LevelManager::getInstance()->getDefaultTile());
				}
				else
				{
					DEBUG_LOG("ASCIIRENDERER", "Rendering non-default tile.");
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
					else if(actor->getClass().compare("BUILDING") == 0)
					{
						renderInfo = *renderInfos->get(((Building*)actor)->getType());
					}
					if(i == renderX + cursorX && j == renderY + cursorY)
					{
						DEBUG_LOG("ASCIIRENDERER", "Setting actor under cursor.");
						actorUnderCursor = actor;
					}
				}
				attron(COLOR_PAIR(renderInfo->colorPair));
				mvprintw(j - renderY, i - renderX, renderInfo->character.c_str());
			}
		}
	}
	move(cursorY, cursorX);
	if(showInspectInfo)
	{
		if(inspectActor != NULL)
		{
			DEBUG_LOG("ASCIIRENDERER", "Printing inspect info for locked actor: " + inspectActor->inspect());
			mvaddstr(0, LevelManager::getInstance()->getWorldWidth() + 10, inspectActor->inspect().c_str());
		}
		else if(actorUnderCursor != NULL)
		{
			DEBUG_LOG("ASCIIRENDERER", "Printing inspect info for actor under cursor: " + actorUnderCursor->inspect());
			mvaddstr(0, LevelManager::getInstance()->getWorldWidth() + 10, actorUnderCursor->inspect().c_str());
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
	if(renderX + dx >= 0 && renderX + dx < (int)(LevelManager::getInstance()->getWorldWidth() - maxX))
	{
		renderX += dx;
	}
	DEBUG_LOG("ASCIIRENDERER", "Camera moved to x value " + std::to_string(renderX) + ".");
}

void ASCIIRenderer::moveY(int dy)
{
	if(renderY + dy >= 0 && renderY + dy < (int)(LevelManager::getInstance()->getWorldHeight() - maxY))
	{
		renderY += dy;
	}
	DEBUG_LOG("ASCIIRENDERER", "Camera moved to y value " + std::to_string(renderY) + ".");
}

void ASCIIRenderer::moveCursorX(int dx)
{
	if(cursorX + dx >= 0 && cursorX + dx < maxX)
	{
		cursorX += dx;
	}
	DEBUG_LOG("ASCIIRENDERER", "Cursor moved to x value " + std::to_string(cursorX) + ".");
}

void ASCIIRenderer::moveCursorY(int dy)
{
	if(cursorY + dy >= 0 && cursorY + dy < maxY)
	{
		cursorY += dy;
	}
	DEBUG_LOG("ASCIIRENDERER", "Cursor moved to y value " + std::to_string(cursorY) + ".");
}

void ASCIIRenderer::setInspectOutput(bool newValue)
{
	showInspectInfo = newValue;
}

void ASCIIRenderer::lockInspectOutput()
{
	DynamicArray<SceneNode*>* nodes = SceneManager::getInstance()->getColliders(renderX = cursorX, renderY + cursorY, false);
	IActor* actor = (*nodes->get(0))->getActor();
	unsigned int i;
	for(i = 1; i < nodes->length(); i++)
	{
		if((*nodes->get(i))->getActor()->getCollisionLayer() > actor->getCollisionLayer())
		{
			actor = (*nodes->get(i))->getActor();
		}
	}
	inspectActor = actor;
}

void ASCIIRenderer::unlockInspectOutput()
{
	inspectActor = NULL;
}

IActor* ASCIIRenderer::getLockedActor()
{
	return inspectActor;
}

int ASCIIRenderer::getCursorWorldX()
{
	return renderX + cursorX;
}

int ASCIIRenderer::getCursorWorldY()
{
	return renderY + cursorY;
}
