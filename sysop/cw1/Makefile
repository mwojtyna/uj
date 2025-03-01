CC=gcc
CFLAGS=-Wall -std=c99 -pedantic

OBJS=1a.o
EXE=1a.x

all: $(EXE)

%.x: %.o
	$(CC) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXE)

.PHONY: all clean
