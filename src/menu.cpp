#include "menu.h"

Menu::Menu() {
    m_menuitem = MenuItem::login;
}

Menu::~Menu() {
}

void Menu::drawMenu() {
    std::string title = "Main Menu - Password Vault";
    std::string instructions = "Use arrow keys to move; Enter to select.";
    std::string menu[MENUMAX] = {
        "Login",
        "Register",
        "Exit"
    };
    clear();
    mvaddstr(1, COLS/2 - title.size()/2, title.c_str());
    for(int i = 0; i < MENUMAX; ++i) {
        if(i == m_menuitem)
            attron(A_REVERSE);
        mvaddstr(5 + (i * 2), COLS/2 - menu[i].size()/2, menu[i].c_str());
        attroff(A_REVERSE);
    }
    mvaddstr(14, COLS/2 - instructions.size()/2, instructions.c_str());
    refresh();
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
            init_pair(1, COLOR_BLACK, COLOR_GREEN);
            bkgd(COLOR_PAIR(1));
            attrset(A_BOLD);
            drawMenu();
            keypad(stdscr, TRUE);
            noecho();
            do {
                key = getch();
                switch(key) {
                    case KEY_DOWN:
                        m_menuitem = static_cast<MenuItem>(static_cast<int>(m_menuitem) + 1);
                        if(m_menuitem > MENUMAX - 1)
                            m_menuitem = MenuItem::login;
                        break;
                    case KEY_UP:
                        m_menuitem = static_cast<MenuItem>(static_cast<int>(m_menuitem) - 1);
                        if(m_menuitem < 0)
                            m_menuitem = MenuItem::quit;
                        break;
                    default:
                        break;
                }
                drawMenu();
            } while(key != '\n');
        }
    }
    echo();
    attroff(A_BOLD);
    endwin();
}

MenuItem Menu::getMenuitem() {
    return m_menuitem;
}
