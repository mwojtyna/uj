DIR=$(notdir $(shell pwd))

CC=gcc
CFLAGS=-Wall -Wno-deprecated-declarations -std=c99 -pedantic -g
LFLAGS=-pthread

DIR=$(notdir $(shell pwd))
PROG=9
OBJS=$(PROG).o
EXE=$(PROG).x
PROCESS_N=3
SECTIONS_N=3

.PHONY: all clean tar run

all: $(EXE)

%.x: %.o
	$(CC) $(LFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXE)

run: $(EXE)
	./$(EXE) $(PROCESS_N) $(SECTIONS_N)

tar: clean
	tar czf ../$(DIR).tar.gz ../$(DIR)
