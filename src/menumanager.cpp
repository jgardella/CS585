#include "menumanager.hh"

MenuManager* MenuManager::instance;

MenuManager::MenuManager()
{
	menuMap = new Trie<MENU*>();
}

MenuManager* MenuManager::getInstance()
{
	if(instance == NULL)
	{
		instance = new MenuManager();
	}
	return instance;
}

void MenuManager::initializeMenu(std::string menuName, DynamicArray<const char*>* menuOptions)
{
	unsigned int j;
	ITEM** items;
	items = new ITEM*[menuOptions->length() + 1];
	for(j = 0; j < menuOptions->length(); j++)
	{
		items[j] = new_item((*menuOptions->get(j)), (*menuOptions->get(j)));
	}
	items[menuOptions->length()] = NULL;
	menuMap->add(menuName, new_menu(items));
}

void MenuManager::setMenu(std::string menuName)
{
	unpost_menu(activeMenu);
	activeMenu = *menuMap->get(menuName);
	post_menu(activeMenu);
}
