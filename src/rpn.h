#ifndef RPN_H_
#define RPN_H_

#include <stddef.h>
#include <stdbool.h>

#define NUMBER 0
#define OP_PLUS '+'
#define OP_MUL '*'
#define OP_MIN '-'
#define OP_DIV '/'

extern const size_t MAXVAL;
extern const bool DEBUG;

typedef struct {
	size_t sp;
	size_t max;
	char values[];
} op_stack_t;

op_stack_t *new_stack(size_t max);
double parse(char *str);
int getop(char *s);
void push(op_stack_t *stack, const double v);
double pop(op_stack_t *stack);

#endif // RPN_H_
