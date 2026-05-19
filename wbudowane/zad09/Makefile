CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O2

TARGET := a.out
SRC := main.cpp
IN ?= in.txt
K1 ?= 1
K2 ?= 1
K3 ?= 1
TMAX ?= 30
FMAX ?= 300
ARGS ?= $(IN) $(K1) $(K2) $(K3) $(TMAX) $(FMAX)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET) $(ARGS)

clean:
	rm -f $(TARGET)
