#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "balanceTree.h"

typedef int Error;

typedef enum
{
    MemoryAllocationError = -1,
    OK = 0
} Errors;

typedef struct Tree
{
    char *key;
    char *value;
    int balance;
    struct Tree *leftChild;
    struct Tree *rightChild;
} Tree;

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

Tree *rotateLeft(Tree *node)
{
    Tree *nodeRightChild = node->rightChild;
    Tree *leftOfRightChild = nodeRightChild->leftChild;
    nodeRightChild->leftChild = node;
    node->rightChild = leftOfRightChild;
    if (nodeRightChild->balance == 0)
    {
        nodeRightChild->balance = -1;
        node->balance = 1;
    }
    else
    {
        nodeRightChild->balance = 0;
        node->balance = 0;
    }
    return nodeRightChild;
}

Tree *rotateRight(Tree *node)
{
    Tree *nodeLeftChild = node->leftChild;
    Tree *rightOfLeftChild = nodeLeftChild->rightChild;
    nodeLeftChild->rightChild = node;
    node->leftChild = rightOfLeftChild;
    if (nodeLeftChild->balance == 0)
    {
        nodeLeftChild->balance = 1;
        node->balance = -1;
    }
    else
    {
        nodeLeftChild->balance = 0;
        node->balance = 0;
    }
    return nodeLeftChild;
}

Tree *bigRotateLeft(Tree *node)
{
    Tree *nodeRightChild = node->rightChild;
    Tree *leftOfRightChild = nodeRightChild->leftChild;
    Tree *leftOfLeftOfRightChild = leftOfRightChild->leftChild;
    Tree *rightOfLeftOfRightChild = leftOfRightChild->rightChild;
    leftOfRightChild->leftChild = node;
    leftOfRightChild->rightChild = nodeRightChild;
    node->rightChild = leftOfLeftOfRightChild;
    nodeRightChild->leftChild = rightOfLeftOfRightChild;
    switch (leftOfRightChild->balance)
    {
    case -1:
        nodeRightChild->balance = 1;
        node->balance = 0;
        break;
    case 0:
        nodeRightChild->balance = 0;
        node->balance = 0;
        break;
    case 1:
        nodeRightChild->balance = 0;
        node->balance = -1;
        break;
    }
    leftOfRightChild->balance = 0;
    return leftOfRightChild;
}

Tree *bigRotateRight(Tree *node)
{
    Tree *nodeLeftChild = node->leftChild;
    Tree *rightOfLeftChild = nodeLeftChild->rightChild;
    Tree *leftOfRightOfLeftChild = rightOfLeftChild->leftChild;
    Tree *rightOfRightOfLeftChild = rightOfLeftChild->rightChild;
    rightOfLeftChild->leftChild = nodeLeftChild;
    rightOfLeftChild->rightChild = node;
    nodeLeftChild->rightChild = leftOfRightOfLeftChild;
    node->leftChild = rightOfRightOfLeftChild;
    switch (rightOfLeftChild->balance)
    {
    case -1:
        nodeLeftChild->balance = 0;
        node->balance = 1;
        break;
    case 0:
        nodeLeftChild->balance = 0;
        node->balance = 0;
        break;
    case 1:
        nodeLeftChild->balance = -1;
        node->balance = 0;
        break;
    }
    rightOfLeftChild->balance = 0;
    return rightOfLeftChild;
}

Tree *balance(Tree *node)
{
    if (node->balance == 2)
    {
        if (node->rightChild->balance >= 0)
        {
            return rotateLeft(node);
        }
        return bigRotateLeft(node);
    }
    if (node->balance == -2)
    {
        if (node->leftChild->balance <= 0)
        {
            return rotateRight(node);
        }
        return bigRotateRight(node);
    }
    return node;
}

Tree *createNode(char *key, char *value)
{
    Tree *newNode = calloc(1, sizeof(Tree));
    newNode->key = calloc(strlen(key) + 1, sizeof(char));
    if (newNode->key == NULL)
    {
        return NULL;
    }
    newNode->value = calloc(strlen(value) + 1, sizeof(char));
    if (newNode->value == NULL)
    {
        return NULL;
    }
    strcpy(newNode->key, key);
    strcpy(newNode->value, value);
    newNode->balance = 0;
    return newNode;
}

Tree *insert(Tree *node, char *key, char *value, bool *isClimb, Error *errorCode)
{
    if (node == NULL)
    {
        Tree *newNode = createNode(key, value);
        if (newNode == NULL)
        {
            *errorCode = MemoryAllocationError;
            *isClimb = false;
        }
        return newNode;
    }

    int balanceDifference = 0;
    if (strcmp(key, node->key) == 0)
    {
        free(node->value);
        node->value = calloc(strlen(value) + 1, sizeof(char));
        if (node->value == NULL)
        {
            *errorCode = MemoryAllocationError;
            *isClimb = false;
        }
        strcpy(node->value, value);
        return node;
    }
    else if (strcmp(key, node->key) < 0)
    {
        node->leftChild = insert(node->leftChild, key, value, isClimb, errorCode);
        --balanceDifference;
    }
    else
    {
        node->rightChild = insert(node->rightChild, key, value, isClimb, errorCode);
        ++balanceDifference;
    }

    if (!*isClimb)
    {
        return node;
    }
    node->balance += balanceDifference;

    if (node->balance == 0 || node->balance == 2 || node->balance == -2)
    {
        *isClimb = false;
    }

    return balance(node);
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