#pragma once

typedef int Error;

typedef enum
{
    OK = 0,
    MemoryAllocationError = -1,
    PointerIsNull = -2
} Errors;

typedef struct List
{
    char *key;
    int value;
    struct List *next;
} List;

// добавляет новый элемент в список
// возвращает одну из Errors
Error addToList(List **head, char *key, int value);

// возвращает
List *findNode(List **head, char *key);

void printList(List *head);

int lengthList(List *head);

void freeList(List *head);