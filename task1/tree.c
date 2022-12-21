#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tree.h"

typedef struct Tree
{
    int key;
    char *value;
    struct Tree *leftChild;
    struct Tree *rightChild;
} Tree;

// a
Error addValue(Tree **root, char *value, int key)
{
    if (*root == NULL)
    {
        *root = calloc(1, sizeof(Tree));
        if (*root == NULL)
        {
            return MemoryAllocationError;
        }
        (*root)->key = key;
        (*root)->value = calloc(strlen(value) + 1, sizeof(char));
        if ((*root)->value == NULL)
        {
            return MemoryAllocationError;
        }
        strcpy((*root)->value, value);
    }

    if (key < (*root)->key)
    {
        addValue(&(*root)->leftChild, value, key);
    }
    else if (key > (*root)->key)
    {
        addValue(&(*root)->rightChild, value, key);
    }
    else if (key == (*root)->key)
    {
        free((*root)->value);
        (*root)->value = calloc(strlen(value) + 1, sizeof(char));
        if ((*root)->value == NULL)
        {
            return MemoryAllocationError;
        }
        strcpy((*root)->value, value);
    }
    return OK;
}

// b and c
char *findValueByKey(Tree *root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (key < root->key)
    {
        findValueByKey(root->leftChild, key);
    }
    else if (key > root->key)
    {
        findValueByKey(root->rightChild, key);
    }
    else
    {
        return root->value;
    }
}

Tree **findNode(Tree **root, int key)
{
    if (*root == NULL)
    {
        return;
    }
    if (key < (*root)->key)
    {
        root = findNode(&(*root)->leftChild, key);
    }
    else if (key > (*root)->key)
    {
        root = findNode(&(*root)->rightChild, key);
    }
    else
    {
        return root;
    }
}

// d
void deleteValue(Tree **root, int key)
{
    if (*root == NULL)
    {
        return;
    }
    Tree **deletedNode = findNode(&(*root), key);
    if (*deletedNode != NULL)
    {
        if ((*deletedNode)->leftChild == NULL) // если слева нет ребенка - просто берем правого
        {
            Tree *freedNode = *deletedNode;
            *deletedNode = (*deletedNode)->rightChild;
            free(freedNode->value);
            free(freedNode);
        }
        else // если слева есть ребенок - ищем максимального потомка слева и ставим на место удаляемого
        {
            Tree *freedNode = *deletedNode;
            Tree *deletedNodeRightChild = (*deletedNode)->rightChild;
            Tree *deletedNodeLeftChild = (*deletedNode)->leftChild;
            Tree *previousNode = *deletedNode;
            *deletedNode = (*deletedNode)->leftChild;
            while ((*deletedNode)->rightChild != NULL)
            {
                previousNode = *deletedNode;
                *deletedNode = (*deletedNode)->rightChild;
            }
            previousNode->rightChild = (*deletedNode)->leftChild;
            (*deletedNode)->rightChild = deletedNodeRightChild;
            if ((*deletedNode) != deletedNodeLeftChild)
            {
                (*deletedNode)->leftChild = deletedNodeLeftChild;
            }
            free(freedNode->value);
            free(freedNode);
        }
    }
}

void printTree(Tree *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%d: %s | ", root->key, root->value);
    printTree(root->leftChild);
    printTree(root->rightChild);
}

void freeTree(Tree **root)
{
    if (*root == NULL)
    {
        return;
    }
    freeTree(&(*root)->leftChild);
    freeTree(&(*root)->rightChild);
    free((*root)->value);
    free(*root);
}