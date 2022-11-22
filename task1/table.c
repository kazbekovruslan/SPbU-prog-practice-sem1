#include <stdlib.h>
#include "table.h"
#include "list.h"

#define hashSize 127

typedef struct Table
{
    int sizeOfTable;
    List *table[hashSize];
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
}

Error addToTable(Table *table, char *word)
{
    if (table == NULL)
    {
        return PointerIsNull;
    }
    List **bucket = &table->table[hash(word)];
    List *entry = findNode(bucket, word);
    if (entry == NULL)
    {
        int errorCode = addToList(bucket, word, 1);
        if (errorCode != OK)
        {
            return errorCode;
        }
        ++table->sizeOfTable;
    }
    else
    {
        ++entry->value;
    }
}

void printTable(Table *table)
{
    for (int i = 0; i < hashSize; ++i)
    {
        printList(table->table[i]);
    }
}

void freeTable(Table *table)
{
    for (int i = 0; i < hashSize; ++i)
    {
        freeList(table->table[i]);
    }
    free(table);
}