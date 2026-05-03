CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O2

TARGET := a.out
SRC := main.cpp
IN ?= in.txt
LIMIT ?= 25
ARGS ?= $(IN) $(LIMIT)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

run: $(TARGET)
	@./$(TARGET) $(ARGS)

clean:
	rm -f $(TARGET)
