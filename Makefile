#Makefile for Assignment 4
#Alexander Zimmermann ZMMALE001

CC=g++

CCFLAGS = -std=c++17
LDFLAGS = -lm -lstdc++fs

SRC = $(wildcard src/*.cpp *.h)
OBJ = $(SRC:.cpp=.o)

PROG = clusterer

$(PROG) : $(OBJ)
	$(CC) $(CCFLAGS) $(SRC) -o clusterer
	
.cpp.o:
	$(CC) $(CCFLAGS) -c $< -o $(LDFLAGS)

depend:
	$(CC) -M $(SRC) > incl.defs

clean:
	rm -f *.o
	rm -f clusterer
