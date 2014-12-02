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
		void initializeMenu(std::string menuName, DynamicArray<char*>* menuOptions);
		void setMenu(std::string menuName);
		std::string getSelectedItem();
		char** getActiveMenu();	
		void disableMenu();
		std::string getAlertString();
		void setAlertString(std::string string);
	private:
		MenuManager();
		MenuManager(MenuManager const&);
		MenuManager& operator=(MenuManager const&);
		~MenuManager();
		
		static MenuManager* instance;
		Trie<char**>* menuMap;
		char** activeMenu;
		std::string alertString;
};

#endif
