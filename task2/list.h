#pragma once

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

List *listCreate();

Error addNumber(List *list, int number);

Error removeNumber(List *list, int number);

Error printList(List *list);

Error freeList(List *list);