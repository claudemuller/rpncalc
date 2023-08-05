#include <stdio.h>
#include "test_rpn.h"

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
