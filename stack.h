#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdio.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} stack_type;

void Stack_Init(stack_type *stack, size_t required_capacity, FILE *log);
void Stack_Push(stack_type *stack, int value, FILE *log);
int Stack_Pop(stack_type *stack, FILE *log);
void Stack_Destroy(stack_type *stack, FILE *log);

void Stack_Dump(FILE *log, stack_type *stack, const char *file_name, int file_line);
#define STACK_DUMP(f, s) Stack_Dump((f), (s), __FILE__, __LINE__)

#endif
