#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "rpn.h"

const bool DEBUG = true;

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("usage: %s <equation>\n", argv[0]);
		return 0;
	}

	printf("= %d\n", parse(argv[1]));

	return 0;
}
