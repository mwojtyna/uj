DIR=$(notdir $(shell pwd))

CC=gcc
CFLAGS=-Wall -std=c99 -pedantic

DIR=$(notdir $(shell pwd))
OBJS=3a.o 3b.o 3c.o 3c1.o
EXE=3a.x 3b.x 3c.x 3c1.x
LIB=lib.c
LIB_H=lib.h

all: $(EXE)

3b.x: 3a.x
3c.x: 3a.x 3c1.x

%.x: %.o $(LIB)
	$(CC) $< $(LIB) -o $@

%.o: %.c $(LIB_H)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXE)

tar: clean
	tar czf ../$(DIR).tar.gz ../$(DIR)

.PHONY: all clean tar
