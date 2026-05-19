CC=g++
CFLAGS=-std=c++20 -Wall -Wpedantic -O2 -g

SRC=z06b.cpp
HDRS=
EXE=a.out

.PHONY: all run

all: $(EXE)

run: $(EXE)
	./$(EXE) ster atom

$(EXE): $(SRC) $(HDRS)
	$(CC) $(CFLAGS) $(SRC) -o $(EXE)

