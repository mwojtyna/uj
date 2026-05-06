CC=g++
CFLAGS=-std=c++20 -Wall -Wpedantic -O2

SRC=z05b.cpp
HDRS=z05b.hpp
EXE=a.out

.PHONY: all run

all: $(EXE)

run: $(EXE)
	./$(EXE)
	dot -Tsvg graph.dot -o graph.svg

$(EXE): $(SRC) $(HDRS)
	$(CC) $(CFLAGS) $(SRC) -o $(EXE)

