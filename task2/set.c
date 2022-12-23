#include <stdio.h>
#include <stdlib.h>
#include "set.h"

typedef struct Node
{
    Value value;
    struct Node *next;
} Node;

typedef struct Set
{
    Node *head;
} Set;

Set *setCreate(Error *errorCode)
{
    Set *set = calloc(1, sizeof(Set));
    if (set == NULL)
    {
        *errorCode = MemoryAllocationError;
    }
    return set;
}

Error addValue(Set *set, Value value)
{
    if (set == NULL)
    {
        return PointerIsNull;
    }

    Node *newNode = calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return MemoryAllocationError;
    }
    newNode->value = value;

    if (set->head == NULL)
    {
        set->head = newNode;
        return OK;
    }
    if (newNode->value < set->head->value)
    {
        newNode->next = set->head;
        set->head = newNode;
        return OK;
    }
    Node *currentNode = set->head;
    Node *previousNode = NULL;
    while (currentNode != NULL && newNode->value > currentNode->value)
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    if (currentNode != NULL && currentNode->value == newNode->value)
    {
        return OK;
    }
    previousNode->next = newNode;
    newNode->next = currentNode;
    return OK;
}

Error setsUnion(Set *firstSet, Set *secondSet, Set *unionSet)
{
    if (firstSet == NULL || secondSet == NULL || unionSet == NULL)
    {
        return PointerIsNull;
    }

    Error errorCode = OK;
    Node *currentNode = firstSet->head;
    while (currentNode != NULL)
    {
        errorCode = addValue(unionSet, currentNode->value);
        if (errorCode != OK)
        {
            return errorCode;
        }
        currentNode = currentNode->next;
    }

    currentNode = secondSet->head;
    while (currentNode != NULL)
    {
        errorCode = addValue(unionSet, currentNode->value);
        if (errorCode != OK)
        {
            return errorCode;
        }
        currentNode = currentNode->next;
    }

    return OK;
}

Error printSet(Set *set)
{
    if (set == NULL)
    {
        return PointerIsNull;
    }
    if (set->head == NULL)
    {
        printf("Set is empty!\n");
        return OK;
    }
    Node *currentNode = set->head;
    while (currentNode != NULL)
    {
        printf("%d ", currentNode->value);
        currentNode = currentNode->next;
    }
    printf("\n");
    return OK;
}

Error freeSet(Set *set)
{
    if (set == NULL)
    {
        return PointerIsNull;
    }
    Node *currentElement = set->head;
    Node *nextElement = NULL;
    while (currentElement != NULL)
    {
        nextElement = currentElement->next;
        free(currentElement);
        currentElement = nextElement;
    }
    free(set);
    return OK;
}