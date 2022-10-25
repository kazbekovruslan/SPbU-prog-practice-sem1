#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"

typedef struct StackElement
{
    int value;
    struct StackElement *next;
} StackElement;

typedef struct Stack 
{
    StackElement *head;
} Stack;

Stack *stackCreate()
{
    Stack *stack = calloc(1, sizeof(stack));
    return stack;
}

int push(Stack *stack, int value)
{
    if (stack == NULL)
    {
        return -1;
    }
    if (stack->head == NULL)
    {
        stack->head = calloc(1, sizeof(StackElement));
        stack->head->value = value;
        return 0;
    }
    StackElement *newElement = calloc(1, sizeof(StackElement));
    if (newElement == NULL)
    {
        return -1;
    }
    newElement->value = value;
    
    newElement->next = stack->head;
    stack->head = newElement;
    return 0;
}

int pop(Stack *stack)
{
    if (stack == NULL)
    {
        return -1;
    }
    int poppedValue = stack->head->value;

    StackElement *headElement = stack->head;
    stack->head = headElement->next;

    free(headElement);
    return poppedValue;
}

int printStack(Stack *stack)
{
    if (stack == NULL)
    {
        return -1;
    }
    StackElement *currentElement = stack->head;
    printf("Stack: ");
    while (currentElement != NULL)
    {
        printf("%d ", currentElement->value);
        currentElement = currentElement->next;
    }
    printf("\n");
    return 0;
}

int len(Stack *stack)
{
    if (stack == NULL)
    {
        return -1;
    }

    StackElement *currentElement = stack->head;
    int length = 0;

    while (currentElement != NULL)
    {
        ++length;
        currentElement = currentElement->next;
    }
    return length;
}

int top(Stack *stack)
{
    if (stack == NULL)
    {
        return -1;
    }
    if (stack->head == NULL)
    {
        return -1;
    }
    return stack->head->value;
}

bool isEmpty(Stack *stack)
{
    if (stack == NULL)
    {
        return -1;
    }
    return stack->head == NULL;
}

int freeStack(Stack *stack)
{
    if (stack == NULL)
    {
        return -1;
    }

    StackElement *currentElement = stack->head;
    while (currentElement != NULL)
    {
        StackElement *nextElement = currentElement->next;
        free(currentElement);
        currentElement = nextElement;
    }
    stack->head = NULL;
    return 0;
}