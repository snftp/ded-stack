#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "stack.h"

#define POP_ERROR 0

void Stack_Dump(FILE *log, stack_type *stack, const char *file_name, int file_line) {
    if (log == NULL) {
        return ;
    }
    fprintf(log, "Stack_Dump called from %s:%d\n", file_name, file_line);
    if (stack == NULL) {
        fprintf(log, "Stack[NULL]\n\n");
        return ;
    }
    fprintf(log, "Stack[%p] {\n", (void*)stack);
    fprintf(log, "  size     = %zu\n", stack->size);
    fprintf(log, "  capacity = %zu\n", stack->capacity);
    fprintf(log, "  data[%p] {\n", (void*)stack->data);
    for (size_t i = 0; i < stack->capacity; ++i) {
        int current_element = stack->data[i];
        if (i < stack->size) {
            fprintf(log, "    *[%zu] = %d\n", i, current_element);
        }
        else {
            fprintf(log, "     [%zu] = %d\n",  i, 0);
        }
    }
    fprintf(log, "  }\n");
    fprintf(log, "}\n\n");
}

void Stack_Init(stack_type *stack, size_t required_capacity, FILE *log) {
    if (stack == NULL) {
        STACK_DUMP(log, NULL);
        return ;
    }
    stack->data = (int*)calloc(required_capacity, sizeof(int));
    if (stack->data == NULL) {
        STACK_DUMP(log, stack);
        return ;
    }
    stack->capacity = required_capacity;
    stack->size = 0;
    STACK_DUMP(log, stack);
}

void Stack_Push(stack_type *stack, int value, FILE *log) {
    if (stack == NULL) {
        STACK_DUMP(log, NULL);
        return ;
    }
    if (stack->size > stack->capacity) {
        fprintf(log, "ERROR: size(%zu) > capacity(%zu)\n", stack->size, stack->capacity);
        STACK_DUMP(log, stack);
        return;
    }
    if (stack->capacity == stack->size) {
        int *new_memory = (int*)realloc(stack->data, stack->capacity * 2 * sizeof(int));
        if (new_memory == NULL) {
            STACK_DUMP(log, stack);
            return ;
        }
        stack->data = new_memory;
        stack->capacity *= 2;
    }
    stack->data[stack->size] = value;
    stack->size++;
    STACK_DUMP(log, stack);
}

int Stack_Pop(stack_type *stack, bool *flag, FILE *log) {
    if (stack == NULL) {
        STACK_DUMP(log, NULL);
        *flag = false;
        return POP_ERROR;
    }
    if (stack->size == 0) {
        fprintf(log, "ERROR: empty stack\n");
        *flag = false;
        STACK_DUMP(log, stack);
        return POP_ERROR;
    }
    stack->size--;
    int value = stack->data[stack->size];
    STACK_DUMP(log, stack);
    return value;
}

void Stack_Destroy(stack_type *stack, FILE *log) {
    if (stack == NULL) {
        STACK_DUMP(log, NULL);
        return ;
    }
    free(stack->data);
    stack->size = 0;
    stack->capacity = 0;
    STACK_DUMP(log, stack);
}


int main() {
    bool flag = true;
    FILE *log = fopen("stack_log.txt", "w");
    if (log == NULL) {
        return 1;
    }
    stack_type stack = {};
    Stack_Init(&stack, 5, log);
    Stack_Push(&stack, 10, log);
    Stack_Push(&stack, 20, log);
    Stack_Push(&stack, 30, log);
    printf("%d\n", Stack_Pop(&stack, &flag, log));
    if (!flag) {
        return 1;
    }
    Stack_Destroy(&stack, log);
    fclose(log);
    return 0;
}
