all: kwatermistrz3000

kwatermistrz3000: main.o osoba.o pietro.o pokoj.o
	g++ main.o osoba.o pietro.o pokoj.o -o kwatermistrz3000 -lncurses
	
main.o: src/main.cpp
	g++ -c src/main.cpp
	
osoba.o: src/osoba.cpp
	g++ -c src/osoba.cpp
	
pietro.o: src/pietro.cpp
	g++ -c src/pietro.cpp
	
pokoj.o: src/pokoj.cpp
	g++ -c src/pokoj.cpp
	
clean:
	rm -rf *.o kwatermistrz3000