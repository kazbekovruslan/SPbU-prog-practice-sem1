#pragma once
#include <stdbool.h>

typedef struct StackElement StackElement;

typedef struct Stack Stack;

Stack *stackCreate();
//creating empty stack

int push(Stack *stack, int value);
//pushing new element on top of the stack

int pop(Stack *stack, int *poppedElement);
//deleting top element of the stack and returning it in variable poppedElement

int printStack(Stack *stack);
//printing stack

int len(Stack *stack, int *lengthOfStack);
//returning length of the stack in variable lengthOfStack

int top(Stack *stack, int *topElement);
//returning top element of the stack in variable topElement

bool isEmpty(Stack *stack);
//checking the stack for emptiness

int freeStack(Stack *stack);
//clearing the stack

//ERRORS:
//all returns -1 because of errors with memory
//all returns -2 because of there is no necessary element