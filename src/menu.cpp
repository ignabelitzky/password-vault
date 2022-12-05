#include "menu.h"

Menu::Menu() {
    m_menuitem = 3;
}

Menu::~Menu() {
}

void Menu::showMenu() {
    int key = 0;
    initscr();
    if(!has_colors()) {
        printw("Sorry your terminal is not supported.\n");
    } else {
        if(start_color() != OK) {
            printw("Unable to start colors.\n");
        } else {
            init_pair(1, COLOR_WHITE, COLOR_BLUE);
            bkgd(COLOR_PAIR(1));
            attrset(A_BOLD);
            drawMenu();
            attroff(A_BOLD);
            keypad(stdscr, TRUE);
            noecho();
            do {
                key = getch();
                switch(key) {
                    case KEY_DOWN:
                        m_menuitem++;
                        if(m_menuitem > MENUMAX - 1)
                            m_menuitem = 0;
                        break;
                    case KEY_UP:
                        m_menuitem--;
                        if(m_menuitem < 0)
                            m_menuitem = MENUMAX - 1;
                        break;
                    default:
                        break;
                }
                drawMenu();
            } while(key != '\n');
        }
    }
    echo();
    endwin();
}

void Menu::drawMenu() {
    std::string mainmenu = "Main Menu";
    std::string menu[MENUMAX] = {
        "Login",
        "Register",
        "Exit"
    };
    clear();
    addstr(mainmenu.c_str());
    for(int i = 0; i < MENUMAX; ++i) {
        if(i == m_menuitem)
            attron(A_REVERSE);
        mvaddstr(3 + (i * 2), 20, menu[i].c_str());
        attroff(A_REVERSE);
    }
    mvaddstr(17, 25, "Use arrow keys to move; Enter to select:");
    refresh();
}
