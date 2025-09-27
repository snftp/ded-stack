#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

void Stack_Init(stack_type *stack, size_t required_capacity) {
    assert(stack != NULL);
    stack->data = (int*)calloc(required_capacity, sizeof(int));
    assert(stack->data != NULL);
    stack->capacity = required_capacity;
    stack->size = 0;
}

void Stack_Push(stack_type *stack, int value) {
    assert(stack != NULL);
    assert(stack->size <= stack->capacity);
    if (stack->capacity == stack->size) {
        int *new_memory = (int*)realloc(stack->data, stack->capacity * 2 * sizeof(int));
        assert(new_memory != NULL);
        stack->data = new_memory;
        stack->capacity *= 2;
    }
    stack->data[stack->size] = value;
    stack->size++;
}

int Stack_Pop(stack_type *stack) {
    assert(stack != NULL);
    assert(stack->size > 0);
    stack->size--;
    return stack->data[stack->size];
}

void Stack_Destroy(stack_type *stack) {
    assert(stack != NULL);
    free(stack->data);
    stack->size = 0;
    stack->capacity = 0;
}

int main() {
    stack_type stack = {};
    Stack_Init(&stack, 5);
    Stack_Push(&stack, 10);
    Stack_Push(&stack, 20);
    Stack_Push(&stack, 30);
    printf("%d\n", Stack_Pop(&stack));
    printf("%d\n", Stack_Pop(&stack));
    printf("%d\n", Stack_Pop(&stack));
    // printf("%d\n", Stack_Pop(&stack)); // NOTE: assert worked
    Stack_Destroy(&stack);
    return 0;
}
