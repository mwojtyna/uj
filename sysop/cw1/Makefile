CC=gcc
CFLAGS=-Wall -std=c99 -pedantic

LIB=lib.o
OBJS=1a.o 1b.o 1c.o 1d.o $(LIB)
EXE=1a.x 1b.x 1c.x 1d.x

all: $(EXE)

%.x: %.o $(LIB)
	$(CC) $< $(LIB) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXE)

.PHONY: all clean
