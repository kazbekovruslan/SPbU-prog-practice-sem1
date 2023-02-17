#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

Error addToList(List **head, char *key, int value)
{
    if (head == NULL)
    {
        return PointerIsNull;
    }
    while (*head != NULL)
    {
        head = &(*head)->next;
    }
    List *newElement = calloc(1, sizeof(List));
    if (newElement == NULL)
    {
        return MemoryAllocationError;
    }
    newElement->key = calloc(strlen(key) + 1, sizeof(char));
    if (newElement->key == NULL)
    {
        return MemoryAllocationError;
    }
    strcpy(newElement->key, key);
    newElement->value = value;
    *head = newElement;
    return OK;
}

List *findNode(List **head, char *key)
{
    if (head == NULL)
    {
        return NULL;
    }
    while (*head != NULL && strcmp((*head)->key, key) != 0)
    {
        head = &(*head)->next;
    }
    return *head;
}

int lengthList(List *head)
{
    int length = 0;
    while (head != NULL)
    {
        ++length;
        head = head->next;
    }
    return length;
}

void printList(List *head)
{
    while (head != NULL)
    {
        printf("%s: %d\n", head->key, head->value);
        head = head->next;
    }
}

void freeList(List *head)
{
    if (head == NULL)
    {
        return;
    }
    freeList(head->next);
    free(head->key);
    free(head);
}