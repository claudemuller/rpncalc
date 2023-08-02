#include <stdio.h>
#include "../src/rpn.h"

#define ASSERT(condition) \
	do { \
		if (!(condition)) { \
			printf("Assertion failed: %s, line %d\n", __FILE__, __LINE__); \
			return 1; \
		} \
	} while (0)

const bool DEBUG = false;

int test_parse() {
    ASSERT(parse("2 2 +") == 4);
    ASSERT(parse("2 2 -") == 0);
    ASSERT(parse("2 4 *") == 8);
    ASSERT(parse("4 2 /") == 2);
    ASSERT(parse("2 4 /") == 0);

    return 0;
}

int main() {
    int failed_tests = 0;

    printf("Running tests for 'parse' function...\n");
    if (test_parse() != 0) {
        printf("Some tests for 'parse' function failed.\n");
        failed_tests++;
    } else {
        printf("All tests for 'parse' function passed.\n");
    }

    if (failed_tests > 0) {
        printf("Total failed tests: %d\n", failed_tests);
        return 1;
    }

    printf("All tests passed successfully\n");

    return 0;
}
