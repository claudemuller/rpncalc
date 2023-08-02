#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "rpn.h"

int parse(char *str)
{
	op_stack_t *stack = (op_stack_t*)malloc(sizeof(op_stack_t) + (MAXVAL * sizeof(double)));
	if (!stack) {
		printf("error alloc'ing mem\n");
		exit(1);
	}

	int type;
	double op2;

	char s[strlen(str)];
	strncpy(s, str, strlen(str));
	char *token = strtok(s, " ");

	!DEBUG ? : printf("parsing: %s\n", str);

	while (token != NULL) {
		type = getop(token);

		switch (type) {
		case NUMBER:
			push(stack, atof(token));
			break;

		case OP_PLUS:
			!DEBUG ? : printf("performing: %c\n", OP_PLUS);
			push(stack, pop(stack) + pop(stack));
			break;

		case OP_MUL:
			!DEBUG ? : printf("performing: %c\n", OP_MUL);
			push(stack, pop(stack) * pop(stack));
			break;

		case OP_MIN:
			!DEBUG ? : printf("performing: %c\n", OP_MIN);
			op2 = pop(stack);
			push(stack, pop(stack) - op2);
			break;

		case OP_DIV:
			!DEBUG ? : printf("performing: %c\n", OP_DIV);
			op2 = pop(stack);
			if (op2 == 0.0) {
				printf("error: zero divisor\n");
			}
			push(stack, pop(stack) / op2);
			break;

		default:
			printf("unknown command %s\n", token);
			break;
		}

		token = strtok(NULL, " ");
	};

	return pop(stack);
}

int getop(char *s)
{
	for (size_t i = 0; i < strlen(s); i++) {
		if (!isdigit(s[i]) && s[i] != '.') {
			return s[i];
		}

		if (isdigit(s[i])) {
			i++;
			continue;
		}

		if (s[i] == '.' && isdigit(s[i+1])) {
			return NUMBER;
		}
	}

	return NUMBER;
}

void push(op_stack_t *stack, const double v)
{
	if (stack->sp >= MAXVAL) {
		printf("error: stack is full, can't push %g\n", v);
		return;
	}

	!DEBUG ? : printf("pushing: %g\n", v);
	stack->values[stack->sp++] = v;
}

double pop(op_stack_t *stack)
{
	if (stack->sp <= 0) {
		printf("error: stack is empty\n");
		return 0.0;
	}

	double t = stack->values[--stack->sp];
	!DEBUG ? : printf("popping: %g\n", t);

	return t;
}

