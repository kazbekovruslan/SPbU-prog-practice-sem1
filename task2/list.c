#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

typedef int Error;

typedef struct Node
{
    int number;
    struct Node *next;
} Node;

typedef struct List
{
    Node *tail;
    Node *head;
} List;

List *listCreate()
{
    List *list = calloc(1, sizeof(List));
    return list;
}

Error addNumber(List *list, int number)
{
    if (list == NULL)
    {
        return -1;
    }

    Node *newNode = calloc(1, sizeof(Node));
    newNode->number = number;

    if (list->head == NULL)
    {
        newNode->next = newNode;
        list->head = newNode;
        list->tail = newNode;
        return 0;
    }

    list->tail->next = newNode;
    newNode->next = list->head;
    list->tail = newNode;
    return 0;
}

Error removeNumbers(List *list, int step)
{
    if (list == NULL)
    {
        return -1;
    }

    Node *currentNode = list->head;
    Node *previousNode = list->tail;
    while (!isLength1(list))
    {
        for (int i = 0; i < step - 1; ++i)
        {
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
        if (currentNode->number == list->head->number) //если удаляется голова
        {
            list->head = currentNode->next;
        }
        if (currentNode->number == list->tail->number) //если удаляется хвост
        {
            list->tail = previousNode;
        }
        previousNode->next = currentNode->next;
        free(currentNode);
        currentNode = previousNode->next;
    }
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
    while (currentNode != list->tail)
    {
        printf("%d ", currentNode->number);
        currentNode = currentNode->next;
    }
    if (currentNode != NULL) printf("%d", currentNode->number);
    printf("\n");
    return 0;
}

bool isLength1(List *list)
{
    if (list->tail == list->head && list->head != NULL)
    {
        return true;
    }
    return false;
}

int lastElement(List *list)
{
    return list->head->number;
}

Error freeList(List *list)
{
    if (list == NULL)
    {
        return -1;
    }
    Node *currentNode = list->head;
    Node *nextElement = NULL;
    while (currentNode != list->tail)
    {
        nextElement = currentNode->next;
        free(currentNode);
        currentNode = nextElement;
    }
    free(currentNode);
    return 0;
}