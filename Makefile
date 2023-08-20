CC = gcc
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
	$(CC) $(CFLAGS) $(LIBS) $(SRC_FILES) -o $(BIN_DIR)/main $(LDFLAGS)

debug:
	$(CC) $(CFLAGS) -g $(LIBS) $(SRC_FILES) -o $(BIN_DIR)/main $(LDFLAGS)

run: build
	@$(BIN_DIR)/main $(ARGS)

test:
	$(CC) $(CFLAGS) -D_GNU_SOURCE $(LIBS) $(TEST_SRC) -o $(TEST_DIR)/tests $(LDFLAGS) && $(TEST_DIR)/tests

test-debug:
	$(CC) $(CFLAGS) -D_GNU_SOURCE -g $(LIBS) $(TEST_SRC) -o $(TEST_DIR)/tests $(LDFLAGS) && lldb $(TEST_DIR)/tests $(ARGS)

clean:
	rm -rf $(BIN_DIR)/* $(TEST_DIR)/tests*
