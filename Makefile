all: run

run:
	g++ src/main.cpp -l sqlite3

removeDatabase:
	rm -i data/passwordVault.db

clean:
	rm a.out
