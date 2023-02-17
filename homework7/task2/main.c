#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void printErrors(Error errorCode)
{
    switch (errorCode)
    {
    case OK:
        break;
    case MemoryAllocationError:
        printf("Memory allocation error!\n");
        break;
    case IncorrectExpression:
        printf("Incorrect expression in input file!\n");
        break;
    }
}

int main()
{
    FILE *file = fopen("../../task2/input.txt", "r");
    if (file == NULL)
    {
        printf("File not found!\n");
        return -2;
    }

    Tree *root = NULL;
    Error errorCode = OK;
    errorCode = buildTree(&root, file);
    if (errorCode != OK)
    {
        printErrors(errorCode);
        freeTree(&root);
        return -1;
    }
    printf("Correct arithmetic expression: ");
    printTree(root);
    printf("\nThe value of an arithmetic expression: %d\n", calculateTree(root));
    freeTree(&root);
    return 0;
}

// тесты для buildTree и calculateTree