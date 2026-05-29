CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O2

TARGET := a.out
SRC := main.cpp
IN ?= in.txt
TIME_MAX ?= 2000
SEED ?= 67
TRY_MAX ?= 10000
ARGS ?= $(IN) $(TIME_MAX) $(SEED) $(TRY_MAX)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET) $(ARGS)

clean:
	rm -f $(TARGET)
