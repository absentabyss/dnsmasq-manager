CC = g++
CFLAGS = -c -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion -std=c++2a

CPP = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp,%.o,$(wildcard *.cpp))

FILENAME = main

out: $(OBJ)
	$(CC) -o $(FILENAME) $^

%.o: %.cpp
	$(CC) -g $(CFLAGS) $^

release:
	$(CC) $(CFLAGS) -O3 $(CPP)
	$(CC) -o $(FILENAME) $(OBJ)

clean:
	rm $(OBJ) $(FILENAME)

