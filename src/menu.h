#include <ncurses.h>
#include <string>
#include "constants.h"

class Menu {
public:
    Menu();
    ~Menu();
    void showMenu();
private:
    int m_menuitem;
    void drawMenu();
};
