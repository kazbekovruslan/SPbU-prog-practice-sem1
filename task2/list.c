#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef struct Node
{
    Value value;
    struct Node *next;
} Node;

typedef struct List
{
    Node *head;
} List;

Error listCreate(List **list)
{
    *list = calloc(1, sizeof(List));
    if (*list == NULL)
    {
        return MemoryAllocationError;
    }
    return OK;
}

Error addValue(List *list, Value value)
{
    if (list == NULL)
    {
        return PointerIsNull;
    }
    if (list->head == NULL)
    {
        list->head = calloc(1, sizeof(Node));
        list->head->value = value;
        return OK;
    }

    Node *newNode = calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return PointerIsNull;
    }
    newNode->value = value;

    Node *currentNode = list->head;
    Node *previousNode = NULL;
    while (currentNode->value < newNode->value && currentNode->next != NULL)
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    if (currentNode == list->head && currentNode->value < newNode->value)
    {
        currentNode->next = newNode;
    }
    else if (previousNode == NULL) // в начало
    {
        newNode->next = currentNode;
        list->head = newNode;
    }
    else if (currentNode->value > newNode->value) // в середину
    {
        previousNode->next = newNode;
        newNode->next = currentNode;
    }
    else // в конец
    {
        currentNode->next = newNode;
        newNode->next = NULL;
    }
    return OK;
}

Error removeValue(List *list, Index index, Value *deletedValue)
{
    if (list == NULL)
    {
        return PointerIsNull;
    }
    if (list->head == NULL)
    {
        return ZeroElementsInList;
    }

    int currentIndex = 0;
    Node *currentElement = list->head;
    Node *previousElement = NULL;
    while (currentIndex != index && currentElement->next != NULL)
    {
        previousElement = currentElement;
        currentElement = currentElement->next;
    }
    if (currentIndex != index) // нет такого индекса
    {
        return NoSuchIndex;
    }
    if (previousElement == NULL) // первый элемент
    {
        list->head = currentElement->next;
    }
    else // остальные элементы
    {
        previousElement->next = currentElement->next;
    }
    *deletedValue = currentElement->value;
    free(currentElement);
    return OK;
}

Error printList(List *list)
{
    if (list == NULL)
    {
        return PointerIsNull;
    }
    if (list->head == NULL)
    {
        printf("List is empty!\n");
        return OK;
    }
    printf("List: ");
    Node *currentNode = list->head;
    while (currentNode != NULL)
    {
        printf("%d ", currentNode->value);
        currentNode = currentNode->next;
    }
    printf("\n");
    return OK;
}

Error freeList(List *list)
{
    if (list == NULL)
    {
        return PointerIsNull;
    }
    Node *currentElement = list->head;
    Node *nextElement = NULL;
    while (currentElement != NULL)
    {
        nextElement = currentElement->next;
        free(currentElement);
        currentElement = nextElement;
    }
    return OK;
}