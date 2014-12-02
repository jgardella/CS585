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
	state = "CAMERA";
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
	for(i = renderX; i < renderX + maxX - 50; i++)
	{
		for(j = renderY; j < renderY + maxY - 2; j++)
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
				attron(COLOR_PAIR(renderInfo->color));
				mvprintw(j - renderY, i - renderX, renderInfo->character.c_str());
			}
		}
	}
	attron(COLOR_PAIR(7));
	drawMenu();
	drawPlayerGold();
	drawWorldState();
	drawInspectInfo(actorUnderCursor);
	drawAlert();
	move(cursorY, cursorX);
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
	unsigned int i;
	DynamicArray<SceneNode*>* nodes = SceneManager::getInstance()->getColliders(renderX + cursorX, renderY + cursorY, false);
	if(nodes->length() > 0)
	{
		IActor* actor = (*nodes->get(0))->getActor();
		for(i = 1; i < nodes->length(); i++)
		{
			if((*nodes->get(i))->getActor()->getCollisionLayer() > actor->getCollisionLayer())
			{
				actor = (*nodes->get(i))->getActor();
			}
		}
		inspectActor = actor;
	}
	else
	{
		inspectActor = NULL;
	}
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

void ASCIIRenderer::drawMenu()
{
	int y = 2;
	char** currentMenu = MenuManager::getInstance()->getActiveMenu();
	int x = maxX - 48 < (unsigned int)LevelManager::getInstance()->getWorldWidth() + 5 ? maxX - 48 : LevelManager::getInstance()->getWorldWidth() + 5;
	if(currentMenu != NULL)
	{
		while(*currentMenu != NULL)
		{
			mvprintw(y, x, *currentMenu);
			currentMenu++;
			y += 2;
		}
	}	
}

void ASCIIRenderer::drawWorldState()
{
	attron(COLOR_PAIR(7));
	int y = maxY - 1 < (unsigned int)LevelManager::getInstance()->getWorldHeight() + 2 ? maxY - 1 : LevelManager::getInstance()->getWorldHeight() + 2;
	mvprintw(y, 0, state.c_str());
}

void ASCIIRenderer::setWorldState(std::string state)
{
	this->state = state;
}

void ASCIIRenderer::drawPlayerGold()
{
	int x = maxX - 48 < (unsigned int)LevelManager::getInstance()->getWorldWidth() + 5 ? maxX - 48 : LevelManager::getInstance()->getWorldWidth() + 5;
	int y = maxY - 1 < (unsigned int)LevelManager::getInstance()->getWorldHeight() + 2 ? maxY - 1 : LevelManager::getInstance()->getWorldHeight() + 2;
	std::string playerGold = "Gold: " + std::to_string(LevelManager::getInstance()->getPlayerGold());
	attron(COLOR_PAIR(3));
	mvprintw(y, x, playerGold.c_str());
}

void ASCIIRenderer::drawAlert()
{
	int y = maxY - 3 < (unsigned int)LevelManager::getInstance()->getWorldHeight() ? maxY - 3 : LevelManager::getInstance()->getWorldHeight();
	mvaddstr(y, 0, MenuManager::getInstance()->getAlertString().c_str());
}

void ASCIIRenderer::drawInspectInfo(IActor* actorUnderCursor)
{
	int y = maxY - 2 < (unsigned int)LevelManager::getInstance()->getWorldHeight() + 1 ? maxY - 2 : LevelManager::getInstance()->getWorldHeight() + 1;
	if(showInspectInfo)
	{
		if(inspectActor != NULL)
		{
			DEBUG_LOG("ASCIIRENDERER", "Printing inspect info for locked actor: " + inspectActor->inspect());
			mvaddstr(y, 0, inspectActor->inspect().c_str());
		}
		else if(actorUnderCursor != NULL)
		{
			DEBUG_LOG("ASCIIRENDERER", "Printing inspect info for actor under cursor: " + actorUnderCursor->inspect());
			mvaddstr(y, 0, actorUnderCursor->inspect().c_str());
		}
	}
}
