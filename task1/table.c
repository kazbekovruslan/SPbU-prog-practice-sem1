#include <stdlib.h>
#include "table.h"
#include "list.h"

#define hashSize 31

typedef struct Table
{
    int amount;
    int size;
    List *hashes[hashSize];
} Table;

int hash(char *key)
{
    int result = 0;
    for (int i = 0; key[i] != '\0'; ++i)
    {
        result = (result + key[i] * 23) % hashSize;
    }
    return result;
}

Error tableCreate(Table **table)
{
    if (table == NULL)
    {
        return PointerIsNull;
    }
    *table = calloc(1, sizeof(Table));
    if (*table == NULL)
    {
        return MemoryAllocationError;
    }
    (*table)->size = hashSize;
    return OK;
}

Error addToTable(Table *table, char *word)
{
    if (table == NULL)
    {
        return PointerIsNull;
    }
    List **bucket = &table->hashes[hash(word)];
    List *entry = findNode(bucket, word);
    if (entry == NULL)
    {
        int errorCode = addToList(bucket, word, 1);
        if (errorCode != OK)
        {
            return errorCode;
        }
        ++table->amount;
    }
    else
    {
        ++entry->value;
    }
    return OK;
}

float loadFactor(Table *table)
{
    if (table == NULL)
    {
        return;
    }
    return table->amount / table->size;
}

int maxLengthList(Table *table)
{
    if (table == NULL)
    {
        return;
    }
    int maxLength = 0;
    for (int i = 0; i < table->size; ++i)
    {
        if (lengthList(table->hashes[i]) > maxLength)
        {
            maxLength = lengthList(table->hashes[i]);
        }
    }
    return maxLength;
}

int averageLengthList(Table *table)
{
    if (table == NULL)
    {
        return;
    }
    int numberOfLists = 0;
    int numberOfNodes = 0;
    for (int i = 0; i < table->size; ++i)
    {
        if (table->hashes[i] != NULL)
        {
            ++numberOfLists;
            numberOfNodes += lengthList(table->hashes[i]);
        }
    }
    return numberOfNodes / numberOfLists;
}

void printTable(Table *table)
{
    if (table == NULL)
    {
        return;
    }
    for (int i = 0; i < table->size; ++i)
    {
        printList(table->hashes[i]);
    }
    return OK;
}

void freeTable(Table *table)
{
    if (table == NULL)
    {
        return;
    }
    for (int i = 0; i < table->size; ++i)
    {
        freeList(table->hashes[i]);
    }
    free(table);
    return OK;
}