CC=g++
CFLAGS=-std=c++20 -Wall -Wpedantic -O2 -g

SRC=z05c.cpp
HDRS=z05c.hpp
EXE=a.out

.PHONY: all run

all: $(EXE)

run: $(EXE)
	@./$(EXE)

$(EXE): $(SRC) $(HDRS)
	$(CC) $(CFLAGS) $(SRC) -o $(EXE)

