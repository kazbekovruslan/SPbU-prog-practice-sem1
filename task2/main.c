#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

typedef enum
{
    OK = 0,
    MemoryAllocationError = -1
} Errors;

int main()
{
    FILE *file = fopen("../../task2/input.txt", "r");
    if (file == NULL)
    {
        printf("File not found!\n");
        return -2;
    }

    Tree *root = NULL;
    if (buildTree(&root, file) == MemoryAllocationError)
    {
        freeTree(&root);
        return -1;
    }
    printf("Correct arithmetic expression: ");
    printTree(root);
    printf("\nThe value of an arithmetic expression: %d\n", calculateTree(root));
    freeTree(&root);
    return 0;
}