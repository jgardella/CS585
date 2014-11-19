#include "menumanager.hh"

MenuManager* MenuManager::instance;

MenuManager::MenuManager()
{
	menuMap = new Trie<char**>();
	activeMenu = NULL;
}

MenuManager* MenuManager::getInstance()
{
	if(instance == NULL)
	{
		instance = new MenuManager();
	}
	return instance;
}

void MenuManager::initializeMenu(std::string menuName, DynamicArray<char*>* menuOptions)
{
	unsigned int i;
	char** arr = new char*[menuOptions->length() + 1];
	for(i = 0; i < menuOptions->length(); i++)
	{
		arr[i] = *menuOptions->get(i);
	}
	arr[menuOptions->length()] = NULL;
	menuMap->add(menuName, arr);
}

void MenuManager::setMenu(std::string menuName)
{
	activeMenu = *menuMap->get(menuName);
}

char** MenuManager::getActiveMenu()
{
	return activeMenu;
}

void MenuManager::disableMenu()
{
	activeMenu = NULL;
}
