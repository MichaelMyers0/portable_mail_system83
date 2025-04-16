#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum {path_len = 255};
enum {capacity = 1024};
typedef char string_t[path_len];
typedef char (*array_pointer)[path_len];
struct stack
{
	string_t stk[capacity];
	int sp;
};
init(stack);
push(stack, string);
pop(stack);
array_pointer top(stack);
#endif
