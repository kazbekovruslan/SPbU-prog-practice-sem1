#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tree.h"

typedef struct Tree
{
    int value;    // значение для числа
    char element; // /,+,*,- и -1, если число
    struct Tree *leftChild;
    struct Tree *rightChild;
} Tree;

Error buildTree(Tree **root, FILE *file)
{
    Error errorCode = OK;
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
            return OK;
        case '+':
        case '*':
        case '/':
        case '-':
            *root = calloc(1, sizeof(Tree));
            if (*root == NULL)
            {
                return MemoryAllocationError;
            }

            (*root)->element = currentSymbol;
            errorCode = buildTree(&(*root)->leftChild, file);
            if (errorCode != OK)
            {
                return errorCode;
            }

            errorCode = buildTree(&(*root)->rightChild, file);
            if (errorCode != OK)
            {
                return errorCode;
            }
            break;
        default: // numbers
            *root = calloc(1, sizeof(Tree));
            if (*root == NULL)
            {
                return MemoryAllocationError;
            }

            (*root)->element = -1;
            ungetc(currentSymbol, file);
            if (fscanf(file, "%d", &(*root)->value) == 0)
            {
                return IncorrectExpression;
            }
            return OK;
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
        return leftResult / rightResult; // деление на 0
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