#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "rpn.h"
#include "utils.h"

const bool DEBUG = true;

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("usage: %s <equation>\n", argv[0]);
		return 0;
	}

	printf("= %g\n", parse(argv[1]));

	return 0;
}
