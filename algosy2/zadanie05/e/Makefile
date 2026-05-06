CC=g++
CFLAGS=-std=c++20 -Wall -Wpedantic -g

SRC=z05e.cpp
HDRS=../c/z05c.hpp
EXE=a.out

.PHONY: all run

all: $(EXE)

run: $(EXE)
	@./$(EXE)

$(EXE): $(SRC) $(HDRS)
	$(CC) $(CFLAGS) $(SRC) -o $(EXE)

