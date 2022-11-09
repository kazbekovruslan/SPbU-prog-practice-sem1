#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef int Error;
typedef int Value;

typedef struct Node
{
    Value value;
    struct Node *next;
} Node;

typedef struct List
{
    Node *head;
} List;

List *listCreate()
{
    List *list = calloc(1, sizeof(List));
    return list;
}

Error addValue(List *list, Value value)
{
    if (list == NULL)
    {
        return -1;
    }
    if (list->head == NULL)
    {
        list->head = calloc(1, sizeof(Node));
        list->head->value = value;
        return 0;
    }

    Node *newNode = calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return -1;
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
    else if (previousNode == NULL) //в начало
    {
        newNode->next = currentNode;
        list->head = newNode;
    }
    else if (currentNode->value > newNode->value) //в середину
    {
        previousNode->next = newNode;
        newNode->next = currentNode;
    }
    else //в конец
    {
        currentNode->next = newNode;
        newNode->next = NULL;
    }
    return 0;
}

Error removeValue(List *list, Value value)
{
    if (list == NULL)
    {
        return -1;
    }
    if (list->head == NULL)
    {
        return -2;
    }

    Node *currentElement = list->head;
    Node *previousElement = NULL;
    while (currentElement->value != value && currentElement->next != NULL)
    {
        previousElement = currentElement;
        currentElement = currentElement->next;
    }
    if (currentElement->value != value) //нет такого элемента
    {
        return -3;
    }
    if (previousElement == NULL) //первый элемент
    {
        list->head = currentElement->next;
    }
    else //остальные элементы
    {
        previousElement->next = currentElement->next;
    }
    free(currentElement);
    return 0;
}

Error printList(List *list)
{
    if (list == NULL)
    {
        return -1;
    }
    printf("List: ");
    Node *currentNode = list->head;
    while (currentNode != NULL)
    {
        printf("%d ", currentNode->value);
        currentNode = currentNode->next;
    }
    printf("\n");
    return 0;
}

Error freeList(List *list)
{
    if (list == NULL)
    {
        return -1;
    }
    Node *currentElement = list->head;
    Node *nextElement = NULL;
    while (currentElement != NULL)
    {
        nextElement = currentElement->next;
        free(currentElement);
        currentElement = nextElement;
    }
    return 0;
}