CC=g++
CFLAGS=-std=c++20 -Wall -Wpedantic -O2

SRC=z04.cpp z04.hpp
EXE=a.out

.PHONY: all run

all: $(EXE)

run: $(EXE)
	@./$(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXE)

