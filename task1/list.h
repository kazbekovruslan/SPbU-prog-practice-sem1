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
// возвращает код ошибки из Errors
Error addToList(List **head, char *key, int value);

// возвращает элемент списка по ключу
List *findNode(List **head, char *key);

// выводит список
void printList(List *head);

//возвращает длину списка
int lengthList(List *head);

//очищает список
void freeList(List *head);