DIR=$(notdir $(shell pwd))

CC=gcc
CFLAGS=-Wall -std=c99 -pedantic

DIR=$(notdir $(shell pwd))
OBJS=3a.o 3b.o
EXE=3a.x 3b.x

all: $(EXE)

3b.x: 3a.x

%.x: %.o
	$(CC) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXE)

tar:
	tar czf ../$(DIR).tar.gz ../$(DIR)

.PHONY: all clean tar
