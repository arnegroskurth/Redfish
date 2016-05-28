
CC=g++
CFLAGS=-Wall -std=c++11 -O3
SOURCES=src/Board.cpp src/Constants.cpp src/Misc.cpp src/Move.cpp src/MoveGenerator.cpp src/PositionMath.cpp


all: main

main:
	$(CC) $(CFLAGS) -o build/redfish main.cpp $(SOURCES)

test:
	$(CC) $(CFLAGS) -o build/test test.cpp $(SOURCES)

clean:
	rm build/*
