CC=g++
CFLAGS=-std=c++20 -Wall -Wpedantic -O2 -g

SRC=z06a.cpp
HDRS=
EXE=a.out
PY=z06a.py

.PHONY: all run

all: $(EXE)

run: $(EXE)
	@./$(EXE)

draw:
	@python $(PY)

$(EXE): $(SRC) $(HDRS)
	$(CC) $(CFLAGS) $(SRC) -o $(EXE)

