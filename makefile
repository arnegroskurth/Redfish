
CC=g++
CFLAGS=-Wall -std=c++11 -O3
SOURCES=src/Board.cpp src/Constants.cpp src/MoveGenerator.cpp


all: clean main computer_vs_computer player_vs_computer test

main:
	$(CC) $(CFLAGS) -o build/redfish main.cpp $(SOURCES)

clean:
	rm -f build/*

computer_vs_computer:
	$(CC) $(CFLAGS) -o build/computer_vs_computer main_computer_vs_computer.cpp $(SOURCES)

player_vs_computer:
	$(CC) $(CFLAGS) -o build/player_vs_computer main_player_vs_computer.cpp $(SOURCES)

test:
	$(CC) $(CFLAGS) -o build/test test.cpp $(SOURCES)
