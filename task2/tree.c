#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Error;

typedef enum
{
    OK = 0,
    MemoryAllocationError = -1
} Errors;

typedef struct Tree
{
    int value;    //значение для числа
    char element; // /,+,*,-,(,) и -1, если число
    struct Tree *leftChild;
    struct Tree *rightChild;
} Tree;

Error buildTree(Tree **root, FILE *file)
{
    while (true)
    {
        char currentSymbol = getc(file);
        switch (currentSymbol)
        {
        case ' ':
        case '(':
            continue;
            break;
        case ')':
            return 0;
        case '+':
        case '*':
        case '/':
            *root = calloc(1, sizeof(Tree));
            if (*root == NULL)
            {
                return MemoryAllocationError;
            }

            (*root)->element = currentSymbol;
            if (buildTree(&(*root)->leftChild, file) == MemoryAllocationError)
            {
                return MemoryAllocationError;
            }

            if (buildTree(&(*root)->rightChild, file) == MemoryAllocationError)
            {
                return MemoryAllocationError;
            }
            break;
        case '-':
            *root = calloc(1, sizeof(Tree));
            if (*root == NULL)
            {
                return MemoryAllocationError;
            }

            char nextSymbol = getc(file);
            ungetc(nextSymbol, file);
            if ((int)nextSymbol >= 48 && (int)nextSymbol <= 57) // negative numbers
            {
                ungetc(currentSymbol, file);
                fscanf(file, "%d", (*root)->value);
                (*root)->element = -1;
            }

            (*root)->element = currentSymbol;
            if (buildTree(&(*root)->leftChild, file) == MemoryAllocationError)
            {
                return MemoryAllocationError;
            }

            if (buildTree(&(*root)->rightChild, file) == MemoryAllocationError)
            {
                return MemoryAllocationError;
            }
            break;
        default: // positive numbers
            *root = calloc(1, sizeof(Tree));
            if (*root == NULL)
            {
                return MemoryAllocationError;
            }

            (*root)->element = -1;
            ungetc(currentSymbol, file);
            fscanf(file, "%d", &(*root)->value);
            return 0;
        }
    }
}

int calculateTree(Tree *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int leftResult = calculateTree(root->leftChild);
    int rightResult = calculateTree(root->rightChild);
    switch (root->element)
    {
    case '+':
        return leftResult + rightResult;
    case '-':
        return leftResult - rightResult;
    case '*':
        return leftResult * rightResult;
    case '/':
        return leftResult / rightResult;
    case -1:
        return root->value;
    }
}

void printTree(Tree *root)
{
    if (root == NULL)
    {
        return;
    }

    if (root->element == -1)
    {
        printf("%d ", root->value);
    }
    else
    {
        printf("( %c ", root->element);
        printTree(root->leftChild);
        printTree(root->rightChild);
        printf(") ");
    }
}

void freeTree(Tree **root)
{
    if (*root == NULL)
    {
        return;
    }
    freeTree(&(*root)->leftChild);
    freeTree(&(*root)->rightChild);
    free(*root);
}