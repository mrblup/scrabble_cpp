.default: all

all: scrabble

clean:
	rm -rf scrabble *.o *.dSYM

scrabble: Tile.o Node.o LinkedList.o scrabble.o Player.o TileBag.o Board.o
	g++ -Wall  -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall  -std=c++14 -g -O -c $^
