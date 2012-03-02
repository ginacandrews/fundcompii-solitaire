all: main
main: main.o CardDeck.o CardColumn.o Board.o
	g++ main.o CardDeck.o CardColumn.o Board.o -o main
main.o: main.cpp
	g++ -c main.cpp
CardDeck.o:  CardDeck.cpp
	g++ -c CardDeck.cpp
CardColumn.o:  CardColumn.cpp
	g++ -c CardColumn.cpp
Board.o: Board.cpp
	g++ -c Board.cpp
clean:
	rm -f *.o main
