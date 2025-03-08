CC=gcc
CFLAGS=-Wall -std=c99 -pedantic

OBJS=2.o potomek.o
EXE=2.x potomek.x

all: $(EXE)

%.x: %.o
	$(CC) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXE)

.PHONY: all clean
