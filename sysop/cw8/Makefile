DIR=$(notdir $(shell pwd))

CC=gcc
CFLAGS=-Wall -Wno-deprecated-declarations -std=c99 -pedantic -g
LFLAGS=-lrt

DIR=$(notdir $(shell pwd))
SERVER=server
CLIENT=client
LIB=libmq

OBJS=$(SERVER).o $(CLIENT).o 
EXE=$(SERVER).x $(CLIENT).x

.PHONY: all clean tar run run_server run_client

all: $(SERVER).x $(CLIENT).x

$(OBJS): $(LIB).h

%.x: %.o $(LIB).o
	$(CC) $(LFLAGS) $< $(LIB).o -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIB).o $(EXE) 

run_server: $(SERVER).x
	./$(SERVER).x

run_client: $(CLIENT).x
	./$(CLIENT).x

run: $(EXE)
	xterm -hold -title SERVER  -bg red   -fg black -e ./$(SERVER).x &
	xterm -hold -title CLIENT1 -bg green -fg black -e ./$(CLIENT).x &
	xterm -hold -title CLIENT2 -bg green -fg black -e ./$(CLIENT).x &

tar: clean
	tar czf ../$(DIR).tar.gz ../$(DIR)
