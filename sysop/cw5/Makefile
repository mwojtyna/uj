DIR=$(notdir $(shell pwd))

CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -g

DIR=$(notdir $(shell pwd))
ZAD5=5a
ZAD5_K = $(ZAD5)_kons
ZAD5_P = $(ZAD5)_prod
PIPE=pipe
INFILE=wejscie.txt
OUTFILE=wyjscie.txt

OBJS=$(ZAD5).o $(ZAD5_K).o $(ZAD5_P).o
EXE=$(ZAD5).x $(ZAD5_K).x $(ZAD5_P).x

.PHONY: all clean tar run

all: $(EXE)

$(ZAD5).x: $(ZAD5_K).x $(ZAD5_P).x

%.x: %.o
	$(CC) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXE) $(OUTFILE) $(PIPE)

tar: clean
	tar czf ../$(DIR).tar.gz ../$(DIR)

run_a: $(ZAD5).x
	set -e && ./$(ZAD5).x $(PIPE) ./$(ZAD5_P).x ./$(ZAD5_K).x $(INFILE) $(OUTFILE) && diff -s $(INFILE) $(OUTFILE)

run_b: $(ZAD5_P).x $(ZAD5_K).x 
	set -e && \
	mkfifo $(PIPE) && \
	xterm -hold -title PRODUCENT -e ./$(ZAD5_P).x $(PIPE) $(INFILE) & \
	xterm -hold -title KONSUMENT -e ./$(ZAD5_K).x $(PIPE) $(OUTFILE) && \
	rm $(PIPE) && \
	diff -s $(INFILE) $(OUTFILE)
