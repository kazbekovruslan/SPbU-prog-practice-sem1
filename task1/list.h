#pragma once

typedef int Error;
typedef int Value;

typedef struct List List;

List *listCreate();

Error addValue(List *list, int value);

Error removeValue(List *list, int value);

Error printList(List *list);

Error freeList(List *list);