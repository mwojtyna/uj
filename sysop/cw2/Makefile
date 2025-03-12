CC=gcc
CFLAGS=-Wall -std=c99 -pedantic

DIR=$(notdir $(shell pwd))
OBJS=2.o
EXE=2.x

all: $(EXE)

%.x: %.o
	$(CC) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXE)

tar: clean
	tar czf ../$(DIR).tar.gz ../$(DIR)

.PHONY: all clean tar
