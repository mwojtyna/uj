DIR=$(notdir $(shell pwd))

CC=gcc
CFLAGS=-Wall -Wno-deprecated-declarations -std=c99 -pedantic -g
LFLAGS=-pthread

DIR=$(notdir $(shell pwd))
DUP=dup
LIB=libsem
WORKER=worker

PROCESS_N ?= 3
SECTIONS_N ?= 3

OBJS=$(DUP).o $(WORKER).o 
EXE=$(DUP).x $(WORKER).x

.PHONY: all clean tar run

$(OBJS): $(LIB).h

all: $(EXE)

%.x: %.o $(LIB).o
	$(CC) $(LFLAGS) $< $(LIB).o -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIB).o $(EXE) numer.txt

run: $(EXE)
	./$(DUP).x ./$(WORKER).x $(PROCESS_N) $(SECTIONS_N)

tar: clean
	tar czf ../$(DIR).tar.gz ../$(DIR)
