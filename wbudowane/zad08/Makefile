CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O2

TARGET := a.out
SRC := main.cpp
OUT ?= out.txt
ARGS ?= 10 2 2 2 0 $(OUT)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET) $(ARGS)

clean:
	rm -f $(TARGET)
