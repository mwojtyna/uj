CC=g++
CFLAGS=-std=c++20 -Wall -Wpedantic -O2

EXE=a.out

.PHONY: all run

all: $(EXE)

run: $(EXE)
	@./$(EXE)

$(EXE): z03a.cpp z03a.hpp
	$(CC) $(CFLAGS) z03a.cpp -o $(EXE)

