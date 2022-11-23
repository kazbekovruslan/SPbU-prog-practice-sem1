#pragma once
#include "list.h"

typedef int Error;

typedef struct Table Table;

int hash(char *key);

Error addToTable(Table *table, char *word);

float loadFactor(Table *table);

int maxLengthList(Table *table);

int averageLengthList(Table *table);

void printTable(Table *table);

void freeTable(Table *table);