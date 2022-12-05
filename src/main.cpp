#include <iostream>
#include <string>
#include <ncurses.h>
#include "sqlite3.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for(int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

class Menu {
private:
    const int menumax = 3;
    int menuitem = 0;
public:
    void drawMenu() {
        char mainmenu[] = "Main Menu";
        char menu[menumax][21] = {
            "Login",
            "Register",
            "Exit"
        };
        clear();
        addstr(mainmenu);
        for(int i = 0; i < menumax; ++i) {
            if(i == menuitem) {
                attron(A_REVERSE);
            }
            mvaddstr(3 + (i * 2), 20, menu[i]);
            attroff(A_REVERSE);
        }
        mvaddstr(17, 25, "Use arrow keys to move; Enter to select:");
        refresh();
    }

    void showMenu() {
        int key = '\0';
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
                        menuitem++;
                        if(menuitem > menumax - 1)
                            menuitem = 0;
                        break;
                    case KEY_UP:
                        menuitem--;
                        if(menuitem < 0)
                            menuitem = menumax - 1;
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
};


int main(int argc, char **argv) {
    sqlite3 *db = NULL;
    int rc = sqlite3_open("data/passwordVault.db", &db);
    char *zErrMsg = NULL;
    std::string sql = "CREATE TABLE IF NOT EXISTS User(" \
        "userID         INT PRIMARY KEY NOT NULL," \
        "name           VARCHAR(50)     NOT NULL," \
        "lastName       VARCHAR(50)     NOT NULL," \
        "email          VARCHAR(80)     NOT NULL," \
        "age            INT             NOT NULL," \
        "gender         CHAR(1)         NOT NULL," \
        "address        VARCHAR(50)," \
        "validationCode VARCHAR(7)      NOT NULL," \
        "username       VARCHAR(50)     NOT NULL," \
        "password       VARCHAR(50)     NOT NULL)";

    if(rc) {
        // database failed to open
        std::cerr << "Can't open database." << std::endl;
    } else {
        // your database code here
        std::cout << "Opened database successfully." << std::endl;
    }
 
    // Execute SQL statement
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    if(rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Table created successfully." << std::endl;
    }

    sqlite3_close(db);
    Menu myMenu;
    myMenu.showMenu();
    
    return 0;
}
