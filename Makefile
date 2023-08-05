CC = gcc
CCFLAGS = -D_GNU_SOURCE
CFLAGS = -std=c99
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror
CFLAGS += -Wmissing-declarations
SRC_FILES = ./src/*.c
BIN_DIR = ./bin
TEST_DIR = ./tests
TEST_SRC = $(filter-out ./src/main.c, $(wildcard ./src/*.c)) $(TEST_DIR)/*.c

build:
	$(CC) $(CFLAGS) -o $(BIN_DIR)/main $(SRC_FILES)

debug:
	$(CC) $(CCFLAGS) $(CFLAGS) -g -o $(BIN_DIR)/main $(SRC_FILES)

run: build
	@$(BIN_DIR)/main $(ARGS)

test:
	$(CC) $(CCFLAGS) $(CCFLAGS) $(CFLAGS) -o $(TEST_DIR)/tests $(TEST_SRC) && $(TEST_DIR)/tests

test-debug:
	$(CC) $(CCFLAGS) $(CFLAGS) -g -o $(TEST_DIR)/tests $(TEST_SRC) && lldb $(TEST_DIR)/tests $(ARGS)

clean:
	rm -rf $(BIN_DIR)/* $(TEST_DIR)/tests*
