CC=g++
CFLAGS=-std=c++23 -Wall -Wpedantic -O2 -g

SRC=z10a.cpp
HDRS=
EXE=a.out

.PHONY: all run

all: $(EXE)

run: $(EXE)
	./$(EXE)

$(EXE): $(SRC) $(HDRS)
	$(CC) $(CFLAGS) $(SRC) -o $(EXE)

