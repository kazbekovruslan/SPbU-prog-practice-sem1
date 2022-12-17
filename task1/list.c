#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

    Node *newNode = calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return -1;
    }
    newNode->value = value;

    if (list->head == NULL)
    {
        list->head = newNode;
        return 0;
    }
    if (newNode->value <= list->head->value)
    {
        newNode->next = list->head;
        list->head = newNode;
        return 0;
    }
    Node *currentNode = list->head;
    Node *previousNode = NULL;
    while (currentNode != NULL && newNode->value > currentNode->value)
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    previousNode->next = newNode;
    newNode->next = currentNode;
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
    if (currentElement->value != value) // нет такого элемента
    {
        return -3;
    }
    if (previousElement == NULL) // первый элемент
    {
        list->head = currentElement->next;
    }
    else // остальные элементы
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
    if (list->head == NULL)
    {
        printf("List is empty!\n");
        return 0;
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

// тесты

bool addTest()
{
    List *list = listCreate();
    if (list == NULL)
    {
        return false;
    }

    int errorCode = 0;
    errorCode = addValue(list, 4);
    if (!(errorCode == 0 && list->head->value == 4))
    {
        return false;
    }

    errorCode = addValue(list, 1);
    if (!(errorCode == 0 && list->head->value == 1 && list->head->next->value == 4 && list->head->next->next == NULL))
    {
        return false;
    }

    errorCode = addValue(list, 3);
    if (!(errorCode == 0 && list->head->value == 1 && list->head->next->value == 3 && list->head->next->next->value == 4 &&
          list->head->next->next->next == NULL))
    {
        return false;
    }

    errorCode = addValue(list, 5);
    if (!(errorCode == 0 && list->head->value == 1 && list->head->next->value == 3 && list->head->next->next->value == 4 &&
          list->head->next->next->next->value == 5 && list->head->next->next->next->next == NULL))
    {
        return false;
    }

    freeList(list);
    free(list);
    return true;
}

bool removeTest()
{
    List *list = listCreate();
    if (list == NULL)
    {
        return false;
    }

    list->head = calloc(1, sizeof(Node));
    if (list->head == NULL)
    {
        return false;
    }
    list->head->value = 1;
    list->head->next = calloc(1, sizeof(Node));
    if (list->head->next == NULL)
    {
        return false;
    }
    list->head->next->value = 2;
    list->head->next->next = calloc(1, sizeof(Node));
    if (list->head->next->next == NULL)
    {
        return false;
    }
    list->head->next->next->value = 3;

    int errorCode = 0;
    errorCode = removeValue(list, 2);
    if (!(errorCode == 0 && list->head->value == 1 && list->head->next->value == 3 && list->head->next->next == NULL))
    {
        return false;
    }
    errorCode = removeValue(list, 3);
    if (!(errorCode == 0 && list->head->value == 1 && list->head->next == NULL))
    {
        return false;
    }
    errorCode = removeValue(list, 1);
    if (!(errorCode == 0 && list->head == NULL))
    {
        return false;
    }
    freeList(list);
    free(list);
    return true;
}

bool tests()
{
    return addTest() && removeTest();
}