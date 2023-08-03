#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/rpn.h"

#define ASSERT(condition) \
	do { \
		if (!(condition)) { \
			printf("Assertion failed: %s, line %d\n", __FILE__, __LINE__); \
			return 1; \
		} \
	} while (0)

#define BUF_SIZE 512

const bool DEBUG = false;

FILE *stderr_stream;
FILE *original_stderr;
char stderr_buf[BUF_SIZE];

void test_setup()
{
    stderr_stream = fmemopen(stderr_buf, BUF_SIZE, "w");
    if (!stderr_stream) {
        perror("error creating stderr stream\n");
        exit(1);
    }

    original_stderr = stderr;
    stderr = stderr_stream;
    setbuf(stderr, NULL);
}

void test_teardown()
{
    stderr = original_stderr;
    fclose(stderr_stream);
}

void reset_stderr()
{
    memset(stderr_buf, 0, sizeof(stderr_buf));
    rewind(stderr);
}

int test_parse()
{
    char *expected, *actual;

    ASSERT(parse("2 2 +") == 4);
    ASSERT(parse("2 2 -") == 0);
    ASSERT(parse("2 4 *") == 8);
    ASSERT(parse("4 2 /") == 2);
    ASSERT(parse("2 4 /") == 0);

    reset_stderr();
    ASSERT(parse("2 0 /") == 0);
    expected = "error: zero divisor\n";
    actual = stderr_buf;
    ASSERT(strcmp(expected, actual) == 0);

    reset_stderr();
    ASSERT(parse("x y +") == 0);
    expected = "error: unknown command x\n";
    actual = stderr_buf;
    ASSERT(strcmp(expected, actual) == 0);

    // ASSERT(parse("2 + 2 2 4 * +") == 12);

    return 0;
}

int test_push()
{
    const int MAX = 3;
    char *expected, *actual;
    op_stack_t *stack = new_stack(MAX);

    push(stack, 2);
    ASSERT(stack->sp == 1);
    ASSERT(stack->values[0] == 2);

    push(stack, 3);
    ASSERT(stack->sp == 2);
    ASSERT(stack->values[0] == 2);
    ASSERT(stack->values[1] == 3);

    push(stack, 4);
    ASSERT(stack->sp == 3);
    ASSERT(stack->values[0] == 2);
    ASSERT(stack->values[1] == 3);
    ASSERT(stack->values[2] == 4);

    reset_stderr();
    push(stack, 4);
    expected = "error: stack is full, can't push 4\n";
    actual = stderr_buf;
    ASSERT(stack->sp == 3);
    ASSERT(strcmp(expected, actual) == 0);

    free(stack);

    return 0;
}

int test_pop()
{
    const int MAX = 3;
    char *expected, *actual;
    op_stack_t *stack = new_stack(MAX);

    stack->values[0] = 2;
    stack->values[1] = 3;
    stack->values[2] = 4;
    stack->sp = 3;

    double val = pop(stack);
    ASSERT(stack->sp == 2);
    ASSERT(val == 4);

    val = pop(stack);
    ASSERT(stack->sp == 1);
    ASSERT(val == 3);

    val = pop(stack);
    ASSERT(stack->sp == 0);
    ASSERT(val == 2);

    reset_stderr();
    val = pop(stack);
    expected = "error: stack is empty\n";
    actual = stderr_buf;
    ASSERT(stack->sp == 0);
    ASSERT(val == 0.0);
    ASSERT(strcmp(expected, actual) == 0);

    free(stack);

    return 0;
}

int main()
{
    test_setup();

    int failed_tests = 0;

    printf("Running tests for 'parse' function...\n");
    if (test_parse() != 0) {
        printf("❌ Some tests for 'parse' function failed.\n");
        failed_tests++;
    } else {
        printf("✅ All tests for 'parse' function passed.\n");
    }

    printf("Running tests for 'push' function...\n");
    if (test_push() != 0) {
        printf("❌ Some tests for 'push' function failed.\n");
        failed_tests++;
    } else {
        printf("✅ All tests for 'push' function passed.\n");
    }

    printf("Running tests for 'pop' function...\n");
    if (test_pop() != 0) {
        printf("❌ Some tests for 'pop' function failed.\n");
        failed_tests++;
    } else {
        printf("✅ All tests for 'pop' function passed.\n");
    }

    if (failed_tests > 0) {
        printf("🥲 Total failed tests: %d\n", failed_tests);
        return 1;
    }

    printf("🥹 All tests passed successfully\n");

    test_teardown();

    return 0;
}
