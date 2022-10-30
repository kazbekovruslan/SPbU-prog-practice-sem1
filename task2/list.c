#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

typedef int Error;
typedef int Value;

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

typedef struct List
{
    Node *head;
} List;

List *listCreate()
{
    List *list = calloc(1, sizeof(list));
    return list;
}