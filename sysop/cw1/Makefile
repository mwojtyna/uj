CC=gcc
CFLAGS=-Wall -std=c99 -pedantic

DIR=$(notdir $(shell pwd))
LIB=lib.o
LIB_H=lib.h
OBJS=1a.o 1b.o 1c.o 1d.o 1e.o $(LIB)
EXE=1a.x 1b.x 1c.x 1d.x 1e.x 

all: $(EXE)

%.x: %.o $(LIB)
	$(CC) $< $(LIB) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): $(LIB_H)

clean:
	rm -f $(OBJS) $(EXE)

tar: clean
	tar czf ../$(DIR).tar.gz ../$(DIR)

.PHONY: all clean tar
