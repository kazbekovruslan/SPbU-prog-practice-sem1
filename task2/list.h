#pragma once

typedef int Error;

typedef struct Node Node;

typedef struct List List;

List *listCreate();

Error addNumber(List *list, int number);

Error removeNumber(List *list, int number);

Error printList(List *list);

Error freeList(List *list);