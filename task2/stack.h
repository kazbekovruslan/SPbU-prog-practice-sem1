#pragma once

typedef int Error;

typedef enum
{
    OK = 0,
    MemoryAllocationError = -1,
    PointerIsNull = -2,
    ZeroElementsOnStack = -3,
    LessThanTwoElementsOnStack = -4
} Errors;

typedef struct Stack Stack;

Error stackCreate(Stack **stack);

Error push(Stack *stack, int value);

Error pop(Stack *stack, int *returningValue);

Error add(Stack *stack);

void printStack(Stack *stack);

void freeStack(Stack *stack);