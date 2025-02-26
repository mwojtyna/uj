CC=gcc
CFLAGS=-Wall -pedantic -g
OBJS=Program9.o lib.o
EXE=a.out

all: $(OBJS)
	$(CC) $(OBJS) -o $(EXE)

%.o: %.c
	$(CC) $(CFLAGS) -c $*.c -o $*.o

clean:
	rm -f $(OBJS) $(EXE) wyniki.txt

.PHONY: all clean
