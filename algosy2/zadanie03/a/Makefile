CC=g++
CFLAGS=-std=c++20 -Wall -Wpedantic -O2

SRC=z03a.cpp z03a.hpp
EXE=a.out

.PHONY: all run

all: $(EXE)

run: $(EXE)
	@./$(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXE)

