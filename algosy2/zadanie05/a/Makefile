SRC ?= ./graph.dot
OUT ?= graph.svg

.PHONY: run

run: $(SRC)
	dot -Tsvg $(SRC) -o $(OUT)
