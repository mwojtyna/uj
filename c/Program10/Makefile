CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -g
LFLAGS=-lm
OBJS=Program10.o lib.o
EXE=a.out

all: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(EXE)

%.o: %.c
	$(CC) $(CFLAGS) -c $*.c -o $*.o

clean:
	rm -f $(OBJS) $(EXE) wyniki.txt

.PHONY: all clean
