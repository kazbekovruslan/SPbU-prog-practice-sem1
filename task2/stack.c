#include <stdio.h>
#include <stdlib.h>

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

Error stackCreate(Stack **stack)
{
    *stack = calloc(1, sizeof(Stack));
    if (*stack == NULL)
    {
        return MemoryAllocationError;
    }
    return OK;
}

Error push(Stack *stack, int value)
{
    if (stack == NULL)
    {
        return PointerIsNull;
    }
    StackElement *newElement = calloc(1, sizeof(StackElement));
    if (newElement == NULL)
    {
        return MemoryAllocationError;
    }
    newElement->value = value;
    newElement->next = stack->head;
    stack->head = newElement;
    return OK;
}

Error pop(Stack *stack, int *returningValue)
{
    if (stack == NULL)
    {
        return PointerIsNull;
    }
    if (stack->head == NULL)
    {
        return ZeroElementsOnStack;
    }
    *returningValue = stack->head->value;
    StackElement *newHead = stack->head->next;
    StackElement *freeingElement = stack->head;
    stack->head = newHead;
    free(freeingElement);
    return OK;
}

Error add(Stack *stack)
{
    if (stack == NULL)
    {
        return PointerIsNull;
    }
    int firstSummand = 0;
    int secondSummand = 0;
    if (pop(stack, &firstSummand) == ZeroElementsOnStack)
    {
        return LessThanTwoElementsOnStack;
    }
    if (pop(stack, &secondSummand) == ZeroElementsOnStack)
    {
        return LessThanTwoElementsOnStack;
    }
    int errorCode = push(stack, firstSummand + secondSummand);
    return errorCode;
}

void printStack(Stack *stack)
{
    printf("Stack: ");
    StackElement *currentElement = stack->head;
    while (currentElement != NULL)
    {
        printf("%d ", currentElement->value);
        currentElement = currentElement->next;
    }
    printf("\n");
}

void freeStack(Stack *stack)
{
    StackElement *currentElement = stack->head;
    StackElement *freeingElement = NULL;
    while (currentElement != NULL)
    {
        freeingElement = currentElement;
        currentElement = currentElement->next;
        free(freeingElement);
    }
}