#pragma once
#include <stdbool.h>

typedef struct StackElement StackElement;

typedef struct Stack Stack;

Stack *stackCreate();
//creating empty stack

int push(Stack *stack, int value);
//pushing new element on top of the stack

int pop(Stack *stack);
//deleting top element of the stack and returning it

int printStack(Stack *stack);
//printing stack

int len(Stack *stack);
//returning length of the stack

int top(Stack *stack);
//returning top element of the stack

bool isEmpty(Stack *stack);
//checking the stack for emptiness

int freeStack(Stack *stack);
//clearing the stack

//all returns -1 because of errors with memory
//returns -2 because of there is no necessary element