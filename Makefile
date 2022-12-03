all: run

run:
	g++ src/main.cpp -lsqlite3 -lncurses

removeDatabase:
	rm -i data/passwordVault.db

clean:
	rm a.out
