DIR=$(notdir $(shell pwd))

CC=gcc
CFLAGS=-Wall -Wno-deprecated-declarations -std=c99 -pedantic -g
LFLAGS=-pthread -lrt

DIR=$(notdir $(shell pwd))
SLIB=lib/libsem

.PHONY: all clean tar run

EXE=7.x
$(OBJS): $(SLIB).h

all: $(EXE)

%.x: %.o $(SLIB).o
	$(CC) $(LFLAGS) $< $(SLIB).o -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(SLIB).o $(EXE) numer.txt

run: $(EXE)
	./$(EXE)

tar: clean
	tar czf ../$(DIR).tar.gz ../$(DIR)
