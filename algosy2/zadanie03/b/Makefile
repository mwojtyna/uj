CC=g++
CFLAGS=-std=c++20 -Wall -Wpedantic -O2

SRC=z03b.cpp z03b.hpp
EXE=a.out

.PHONY: all run

all: $(EXE)

run: $(EXE)
	@./$(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXE)

