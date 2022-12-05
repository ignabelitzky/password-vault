all: run

run:
	g++ -c src/menu.cpp src/main.cpp -lsqlite3 -lncurses
	g++ menu.o main.o -lsqlite3 -lncurses

removeDatabase:
	rm -i data/passwordVault.db

clean:
	rm a.out
