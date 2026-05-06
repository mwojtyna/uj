CC=g++
CFLAGS=-std=c++20 -Wall -Wpedantic -O2

SRC=z05d.cpp
HDRS=../c/z05c.hpp
EXE=a.out

GRAPH_SRC=graph.dot
GRAPH_OUT=graph.svg

.PHONY: all run

all: $(EXE)

run: $(EXE)
	@./$(EXE)
	dot -Tsvg $(GRAPH_SRC) -o $(GRAPH_OUT)

$(EXE): $(SRC) $(HDRS)
	$(CC) $(CFLAGS) $(SRC) -o $(EXE)

