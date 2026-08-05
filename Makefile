CC = gcc
CFLAGS = -Wall -Wextra -std=c11
BIN_DIR = bin
SRC = $(wildcard ejemplos/unidad-2/*.c) $(wildcard ejemplos/unidad-3/*.c)
BINS = $(patsubst ejemplos/%.c,$(BIN_DIR)/%,$(SRC))

.PHONY: all clean

all: $(BINS)

$(BIN_DIR)/unidad-2/%: ejemplos/unidad-2/%.c
	@mkdir -p $(BIN_DIR)/unidad-2
	$(CC) $(CFLAGS) -o $@ $<

$(BIN_DIR)/unidad-3/%: ejemplos/unidad-3/%.c
	@mkdir -p $(BIN_DIR)/unidad-3
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(BIN_DIR)/unidad-2 $(BIN_DIR)/unidad-3
