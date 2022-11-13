#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

Tree *rotateLeft(Tree *node)
{
    Tree *nodeRightChild = node->rightChild;
    Tree *rightLeftChild = nodeRightChild->leftChild;
    nodeRightChild->leftChild = node;
    node->rightChild = rightLeftChild;
    if (nodeRightChild->balance == 0)
    {
        nodeRightChild->balance = 1;
        node->balance = 0;
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
    Tree *rightLeftChild = nodeLeftChild->rightChild;
    nodeLeftChild->rightChild = node;
    node->leftChild = rightLeftChild;
    if (nodeLeftChild->balance == 0)
    {
        nodeLeftChild->balance = 1;
        node->balance = 0;
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
    node->rightChild = rotateRight(node->rightChild);
    return rotateLeft(node);
}

Tree *bigRotateRight(Tree *node)
{
    node->leftChild = rotateLeft(node->leftChild);
    return rotateRight(node);
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

Tree *addValue(Tree *node, char *key, char *value)
{
    if (node == NULL)
    {
        Tree *newNode = calloc(1, sizeof(Tree));
        newNode->key = calloc(strlen(key) + 1, sizeof(char));
        newNode->value = calloc(strlen(value) + 1, sizeof(char));
        strcpy(newNode->key, key);
        strcpy(newNode->value, value);
        newNode->balance = 0;
        return newNode;
    }

    if (strcmp(key, node->key) < 0)
    {
        node->leftChild = insert(node->leftChild, key, value);
        --node->balance;
    }
    else if (strcmp(key, node->key) > 0)
    {
        node->rightChild = insert(node->rightChild, key, value);
        ++node->balance;
    }
    else
    {
        free(node->value);
        node->value = calloc(strlen(value) + 1, sizeof(char));
        strcpy(node->value, value);
    }

    return balance(node);
}

Tree *deleteValue(Tree *node, char *key)
{
}

// a
// Error addValue(Tree **root, char *value, int key)
// {
//     if (*root == NULL)
//     {
//         *root = calloc(1, sizeof(Tree));
//         if (*root == NULL)
//         {
//             return MemoryAllocationError;
//         }
//         (*root)->key = key;
//         (*root)->value = calloc(strlen(value) + 1, sizeof(char));
//         if ((*root)->value == NULL)
//         {
//             return MemoryAllocationError;
//         }
//         strcpy((*root)->value, value);
//     }

//     if (key < (*root)->key)
//     {
//         addValue(&(*root)->leftChild, value, key);
//     }
//     else if (key > (*root)->key)
//     {
//         addValue(&(*root)->rightChild, value, key);
//     }
//     else if (key == (*root)->key)
//     {
//         free((*root)->value);
//         (*root)->value = calloc(strlen(value) + 1, sizeof(char));
//         if ((*root)->value == NULL)
//         {
//             return MemoryAllocationError;
//         }
//         strcpy((*root)->value, value);
//     }
//     return OK;
// }

// d
// void deleteValue(Tree **root, int key)
// {
//     if (*root == NULL)
//     {
//         return;
//     }
//     Tree **deletedNode = findNode(&(*root), key);
//     if (*deletedNode != NULL)
//     {
//         if ((*deletedNode)->leftChild == NULL) //если слева нет ребенка - просто берем правого
//         {
//             Tree *freedNode = *deletedNode;
//             *deletedNode = (*deletedNode)->rightChild;
//             free(freedNode->value);
//             free(freedNode);
//         }
//         else //если слева есть ребенок - ищем максимального потомка слева и ставим на место удаляемого
//         {
//             Tree *freedNode = *deletedNode;
//             Tree *deletedNodeRightChild = (*deletedNode)->rightChild;
//             Tree *deletedNodeLeftChild = (*deletedNode)->leftChild;
//             Tree *previousNode = *deletedNode;
//             *deletedNode = (*deletedNode)->leftChild;
//             while ((*deletedNode)->rightChild != NULL)
//             {
//                 previousNode = *deletedNode;
//                 *deletedNode = (*deletedNode)->rightChild;
//             }
//             previousNode->rightChild = NULL;
//             (*deletedNode)->rightChild = deletedNodeRightChild;
//             if ((*deletedNode) != deletedNodeLeftChild)
//             {
//                 (*deletedNode)->leftChild = deletedNodeLeftChild;
//             }
//             free(freedNode->value);
//             free(freedNode);
//         }
//     }
// }

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