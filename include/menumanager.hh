#ifndef _MENUMANAGER_HH_
#define _MENUMANAGER_HH_

#include <string>
#include <menu.h>
#include "trie.hh"
#include "dynamicarray.hh"

#ifndef NULL
#define NULL 0
#endif

class MenuManager
{
	public:
		static MenuManager* getInstance();
		void initializeMenus(Trie<DynamicArray<std::string>*>* menuInfo);
		void setMenu(std::string menuName);
		std::string getSelectedItem();
		
	private:
		MenuManager();
		MenuManager(MenuManager const&);
		MenuManager& operator=(MenuManager const&);
		~MenuManager();
		
		static MenuManager* instance;
		Trie<MENU*>* menuMap;
		MENU* activeMenu;
};

#endif
