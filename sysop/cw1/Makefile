CC=gcc
CFLAGS=-Wall -std=c99 -pedantic

LIB=lib.o
OBJS=1a.o 1b.o 1c.o 1d.o 1e.o $(LIB)
EXE=1a.x 1b.x 1c.x 1d.x 1e.x

all: $(EXE)

%.x: %.o $(LIB)
	$(CC) $< $(LIB) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXE)

.PHONY: all clean
