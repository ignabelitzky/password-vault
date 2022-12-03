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
public:
     void showMenu() {
        initscr();
        printw("My Menu!\n");
        refresh();
        getch();
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
