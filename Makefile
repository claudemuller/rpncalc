SRC=./src
BIN=./bin
TESTS=./tests

build:
	gcc -o $(BIN)/main $(SRC)/*.c

debug:
	gcc -g -o $(BIN)/main $(SRC)/*.c

run: build
	@$(BIN)/main $(ARGS)

test:
	gcc -o $(TESTS)/tests $(SRC)/rpn.c $(TESTS)/test_rpn.c && $(TESTS)/tests

test-debug:
	gcc -g -o $(TESTS)/tests $(SRC)/rpn.c $(TESTS)/test_rpn.c

clean:
	rm -rf $(BIN)/* $(TESTS)/tests
