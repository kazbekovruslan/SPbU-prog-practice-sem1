#include <stdio.h>
#include <stdlib.h>
#include "table.h"

#define maxLength 256

int main()
{
    FILE *file = fopen("../../task1/input.txt", "r");
    if (file == NULL)
    {
        printf("File not found!\n");
        return -3;
    }

    Table *table = NULL;
    Error errorCode = tableCreate(&table);
    if (errorCode == MemoryAllocationError)
    {
        printf("Memory error!\n");
    }
    char word[maxLength] = {0};

    while (fscanf(file, "%s", word) == 1)
    {
        errorCode = addToTable(table, word);
        if (errorCode == MemoryAllocationError)
        {
            printf("Memory error!\n");
            return errorCode;
        }
    }
    printTable(table);
    printf("Load factor = %f\n", loadFactor(table));
    printf("Max length of list = %d\n", maxLengthList(table));
    printf("Average length of list = %d\n", averageLengthList(table));
    return OK;
}