#include "menumanager.hh"

MenuManager::MenuManager()
{

}

MenuManager* MenuManager::getInstance()
{
	if(instance == NULL)
	{
		instance = new MenuManager();
	}
	return instance;
}

void MenuManager::initializeMenus(Trie<DynamicArray<std::string>*>* menuInfo)
{
	unsigned int i, j;
	MENU* menu;
	ITEM** items;
	DynamicArray<std::string>* menuStrings;
	DynamicArray<std::string>* keys = menuInfo->getKeys();
	for(i = 0; i < keys->length(); i++)
	{
		menuStrings = *menuInfo->get(*keys->get(i));
		items = new ITEM*[menuStrings->length() + 1];
		for(j = 0; j < menuStrings->length(); j++)
		{
			items[j] = new_item((*menuStrings->get(j)).c_str(), (*menuStrings->get(j)).c_str());
		}
		items[menuStrings->length()] = NULL;
		menuMap->add(*keys->get(i), new_menu(items));
	}
}

void MenuManager::setMenu(std::string menuName)
{
	unpost_menu(activeMenu);
	activeMenu = *menuMap->get(menuName);
	post_menu(activeMenu);
}
