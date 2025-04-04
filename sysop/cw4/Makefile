DIR=$(notdir $(shell pwd))

CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -g

DIR=$(notdir $(shell pwd))
ZAD4=4
INFILE=wejscie.txt
OUTFILE=wyjscie.txt

OBJS=$(ZAD4).o
EXE=$(ZAD4).x

all: $(EXE)

%.x: %.o
	$(CC) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXE)

tar: clean
	tar czf ../$(DIR).tar.gz ../$(DIR)

run: $(ZAD4).x
	./$(ZAD4).x $(INFILE) $(OUTFILE) && diff -s $(INFILE) $(OUTFILE)

.PHONY: all clean tar run
