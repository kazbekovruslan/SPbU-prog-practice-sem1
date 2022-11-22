#pragma once
#include "list.h"

typedef int Error;

typedef struct Table Table;

int hash(char *key);

Error addToTable(Table *table, char *word);

void printTable(Table *table);

void freeTable(Table *table);