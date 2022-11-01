#pragma once
#include <stdbool.h>

typedef int Error;

typedef struct Node Node;

typedef struct List List;

List *listCreate();

Error addNumber(List *list, int number);

Error removeNumbers(List *list, int step);

Error printList(List *list);

bool isLength1(List *list);

Error firstElement(List *list, int *lastStanding);

Error freeList(List *list);