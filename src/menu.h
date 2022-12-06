#include <ncurses.h>
#include <string>
#include "constants.h"

enum MenuItem {
    login,
    record,
    quit
};

class Menu {
private:
    MenuItem m_menuitem;
    void drawMenu();
public:
    Menu();
    ~Menu();
    void showMenu();
    MenuItem getMenuitem();
};
