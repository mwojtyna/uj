DIR := $(notdir $(CURDIR))

CC := gcc
CFLAGS := -Wall -Wno-deprecated-declarations -std=gnu99 -pedantic -g
LDFLAGS := -lrt

EXE := 7
EXED1 := 7_dyn1
EXED2 := 7_dyn2
PROD := 7_prod
KONS := 7_kons
INFILE := wejscie.txt
OUTFILE := wyjscie.txt

LIB_DIR := ./lib
LIB_NAME := libsysop
LIBSEM := $(LIB_DIR)/sem
LIBSHM := $(LIB_DIR)/shm
SLIB := $(LIB_DIR)/$(LIB_NAME).a
DLIB := $(LIB_DIR)/$(LIB_NAME).so

.PHONY: all clean tar run_static run_dynamic1 run_dynamic2

all: $(EXE).x $(EXED1).x $(EXED2).x $(PROD).x $(KONS).x

%.x: %.o $(SLIB)
	$(CC) $(LDFLAGS) $< $(SLIB) -o $@

$(EXE).x: $(EXE).o $(SLIB)
	$(CC) $(LDFLAGS) $< $(SLIB) -o $@

$(EXED1).x: $(EXE).o $(DLIB)
	$(CC) $(LDFLAGS) -L$(LIB_DIR) -lsysop $< -o $@ -Wl,-R$(LIB_DIR)

$(EXED2).x: $(EXE).o $(DLIB)
	$(CC) $(LDFLAGS) -L$(LIB_DIR) -lsysop $< -o $@

$(SLIB): $(LIBSEM).o $(LIBSHM).o
	ar rcs $@ $^

$(DLIB): $(LIBSEM).o $(LIBSHM).o
	$(CC) -shared -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.a *.so *.x $(LIB_DIR)/*.o $(LIB_DIR)/*.a $(LIB_DIR)/*.so $(LIB_DIR)/*.x $(OUTFILE)

run_static: $(EXE).x $(PROD).x $(KONS).x
	./$(EXE).x ./$(PROD).x ./$(KONS).x $(INFILE) $(OUTFILE)
	diff -s $(INFILE) $(OUTFILE)

run_dynamic1: $(EXED1).x $(PROD).x $(KONS).x
	./$(EXED1).x ./$(PROD).x ./$(KONS).x $(INFILE) $(OUTFILE)
	diff -s $(INFILE) $(OUTFILE)

run_dynamic2: $(EXED2).x $(PROD).x $(KONS).x
	LD_LIBRARY_PATH=$(LIB_DIR):$LD_LIBRARY_PATH ./$(EXED2).x ./$(PROD).x ./$(KONS).x $(INFILE) $(OUTFILE)
	diff -s $(INFILE) $(OUTFILE)

tar: clean
	tar czf ../$(DIR).tar.gz ../$(DIR)

