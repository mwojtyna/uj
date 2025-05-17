DIR=$(notdir $(shell pwd))

CC=gcc
CFLAGS=-Wall -Wno-deprecated-declarations -std=gnu99 -pedantic -fpic -g
LFLAGS=-pthread -lrt

DIR=$(notdir $(shell pwd))
EXE=7
EXED1=7_dyn1
EXED2=7_dyn2
PROD=7_prod
KONS=7_kons
INFILE=wejscie.txt
OUTFILE=wyjscie.txt
LIB_DIR=./lib
LIB_NAME=libsysop
LIBSEM=$(LIB_DIR)/sem
LIBSHM=$(LIB_DIR)/shm
SLIB=$(LIB_DIR)/$(LIB_NAME).a
DLIB=$(LIB_DIR)/$(LIB_NAME).so

.PHONY: all clean tar run_static run_dyn1 run_dyn2

all: $(EXE).x $(EXED1).x $(EXED2).x $(PROD).x $(KONS).x

$(EXED1).x: $(EXE).o $(DLIB)
	$(CC) $(LFLAGS) -L$(LIB_DIR) -lsysop $< -o $@ -Wl,-R $(LIB_DIR)

$(EXED2).x: $(EXE).o $(DLIB)
	$(CC) $(LFLAGS) -L$(LIB_DIR) -lsysop $< -o $@

%.x: %.o $(SLIB)
	$(CC) $(LFLAGS) $< $(SLIB) -o $@

$(SLIB): $(LIBSEM).o $(LIBSHM).o
	ar -rcs $(SLIB) $(LIBSEM).o $(LIBSHM).o

$(DLIB): $(LIBSEM).o $(LIBSHM).o
	$(CC) -shared $(LIBSEM).o $(LIBSHM).o -o $(DLIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f ./*.{o,a,so,x} ./**/*.{o,a,so,x} wyjscie.txt

run_static: $(EXE).x $(PROD).x $(KONS).x
	./$(EXE).x ./$(PROD).x ./$(KONS).x $(INFILE) $(OUTFILE)
	diff -s $(INFILE) $(OUTFILE)

run_dynamic1: $(EXED1).x $(PROD).x $(KONS).x
	./$(EXED1).x ./$(PROD).x ./$(KONS).x $(INFILE) $(OUTFILE)
	diff -s $(INFILE) $(OUTFILE)

run_dynamic2: $(EXED2).x $(PROD).x $(KONS).x
	export LD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH}; \
	./$(EXED2).x ./$(PROD).x ./$(KONS).x $(INFILE) $(OUTFILE)
	diff -s $(INFILE) $(OUTFILE)

tar: clean
	tar czf ../$(DIR).tar.gz ../$(DIR)
