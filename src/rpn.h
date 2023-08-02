#ifndef RPN_H_
#define RPN_H_

#include <stddef.h>
#include <stdbool.h>

#define MAXVAL 100

#define NUMBER 0
#define OP_PLUS '+'
#define OP_MUL '*'
#define OP_MIN '-'
#define OP_DIV '/'

extern const bool DEBUG;

typedef struct {
	size_t sp;
	char values[MAXVAL];
} op_stack_t;

int parse(char *str);
int getop(char *s);
void push(op_stack_t *stack, const double v);
double pop(op_stack_t *stack);

#endif // RPN_H_
