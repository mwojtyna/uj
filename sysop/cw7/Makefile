DIR=$(notdir $(shell pwd))

CC=gcc
CFLAGS=-Wall -Wno-deprecated-declarations -std=gnu99 -pedantic -fpic -g
LFLAGS=-pthread -lrt

DIR=$(notdir $(shell pwd))
EXE=7
EXED1=7_dyn1
EXED2=7_dyn2
LIB_DIR=./lib
LIB_NAME=libsysop
LIBSEM=$(LIB_DIR)/sem
LIBSHM=$(LIB_DIR)/shm
SLIB=$(LIB_DIR)/$(LIB_NAME).a
DLIB=$(LIB_DIR)/$(LIB_NAME).so

.PHONY: all clean tar run_static run_dyn1 run_dyn2

all: $(EXE).x $(EXED1).x $(EXED2).x

$(EXE).x: $(EXE).o $(SLIB)
	$(CC) $(LFLAGS) $< $(SLIB) -o $@

$(EXED1).x: $(EXE).o $(DLIB)
	$(CC) $(LFLAGS) -L$(LIB_DIR) -lsysop $< -o $@ -Wl,-R $(LIB_DIR)

$(EXED2).x: $(EXE).o $(DLIB)
	$(CC) $(LFLAGS) -L$(LIB_DIR) -lsysop $< -o $@

$(SLIB): $(LIBSEM).o $(LIBSHM).o
	ar -rcs $(SLIB) $(LIBSEM).o $(LIBSHM).o

$(DLIB): $(LIBSEM).o $(LIBSHM).o
	$(CC) -shared $(LIBSEM).o $(LIBSHM).o -o $(DLIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.{o,a,so,x} **/*.{o,a,so,x}

run_static: $(EXE).x
	./$(EXE).x

run_dynamic1: $(EXED1).x
	./$(EXED1).x

run_dynamic2: $(EXED2).x
	export LD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH}; \
	./$(EXED2).x \

tar: clean
	tar czf ../$(DIR).tar.gz ../$(DIR)
