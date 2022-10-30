#pragma once
#include <stdbool.h>

typedef int Error;

typedef struct Node Node;

typedef struct List List;

List *listCreate();

Error addNumber(List *list, int number);

Error removeNumber(List *list, int number);

Error printList(List *list);

bool isLength1(List *list);

Error freeList(List *list);