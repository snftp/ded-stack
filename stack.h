#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} stack_type;

void Stack_Init(stack_type *stack, size_t required_capacity);
void Stack_Push(stack_type *stack, int value);
int Stack_Pop(stack_type *stack); // give the last added value
void Stack_Destroy(stack_type *stack); // free data; size, capacity < 0
// void Stack_Dump(stack_type *stack); // print current state of stack, errors, etc; not into console but some file

#endif
