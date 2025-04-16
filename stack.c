#include "stack.h"

init(stack)
stack_t* stack;
{
	stack->sp = 0;
}

push(stack, string)
stack_t* stack;
string_t string;
{
	if (stack->sp >= capacity)
	{
		fprintf(stderr, "ERROR: Stack overflow\n");
		exit(1);
	}
	strcpy(stack->stk[stack->sp], string);
	(stack->sp)++;
}

pop(stack)
stack_t* stack;	
{
	if (stack->sp <= 0)
	{
		fprintf(stderr, "ERROR: stack underflow\n");
		exit(2);
	}
	(stack->sp)--;
}

array_pointer top(stack)
stack_t* stack;
{
	return stack->stk[stack->sp - 1];
}
