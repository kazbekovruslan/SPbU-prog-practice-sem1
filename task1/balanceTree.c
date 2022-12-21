#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "balanceTree.h"

typedef struct Tree
{
    char *key;
    char *value;
    int balance;
    struct Tree *leftChild;
    struct Tree *rightChild;
} Tree;

char *findValueByKey(Tree *node, char *key)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (strcmp(key, node->key) < 0)
    {
        findValueByKey(node->leftChild, key);
    }
    else if (strcmp(key, node->key) > 0)
    {
        findValueByKey(node->rightChild, key);
    }
    else
    {
        return node->value;
    }
}

Tree *rotateLeft(Tree *node)
{
    Tree *deletedNodeRightChild = node->rightChild;
    Tree *leftOfRightChild = deletedNodeRightChild->leftChild;
    deletedNodeRightChild->leftChild = node;
    node->rightChild = leftOfRightChild;
    if (deletedNodeRightChild->balance == 0)
    {
        deletedNodeRightChild->balance = -1;
        node->balance = 1;
    }
    else
    {
        deletedNodeRightChild->balance = 0;
        node->balance = 0;
    }
    return deletedNodeRightChild;
}

Tree *rotateRight(Tree *node)
{
    Tree *deletedNodeLeftChild = node->leftChild;
    Tree *rightOfLeftChild = deletedNodeLeftChild->rightChild;
    deletedNodeLeftChild->rightChild = node;
    node->leftChild = rightOfLeftChild;
    if (deletedNodeLeftChild->balance == 0)
    {
        deletedNodeLeftChild->balance = 1;
        node->balance = -1;
    }
    else
    {
        deletedNodeLeftChild->balance = 0;
        node->balance = 0;
    }
    return deletedNodeLeftChild;
}

Tree *bigRotateLeft(Tree *node)
{
    Tree *deletedNodeRightChild = node->rightChild;
    Tree *leftOfRightChild = deletedNodeRightChild->leftChild;
    Tree *leftOfLeftOfRightChild = leftOfRightChild->leftChild;
    Tree *rightOfLeftOfRightChild = leftOfRightChild->rightChild;
    leftOfRightChild->leftChild = node;
    leftOfRightChild->rightChild = deletedNodeRightChild;
    node->rightChild = leftOfLeftOfRightChild;
    deletedNodeRightChild->leftChild = rightOfLeftOfRightChild;
    switch (leftOfRightChild->balance)
    {
    case -1:
        deletedNodeRightChild->balance = 1;
        node->balance = 0;
        break;
    case 0:
        deletedNodeRightChild->balance = 0;
        node->balance = 0;
        break;
    case 1:
        deletedNodeRightChild->balance = 0;
        node->balance = -1;
        break;
    }
    leftOfRightChild->balance = 0;
    return leftOfRightChild;
}

Tree *bigRotateRight(Tree *node)
{
    Tree *deletedNodeLeftChild = node->leftChild;
    Tree *rightOfLeftChild = deletedNodeLeftChild->rightChild;
    Tree *leftOfRightOfLeftChild = rightOfLeftChild->leftChild;
    Tree *rightOfRightOfLeftChild = rightOfLeftChild->rightChild;
    rightOfLeftChild->leftChild = deletedNodeLeftChild;
    rightOfLeftChild->rightChild = node;
    deletedNodeLeftChild->rightChild = leftOfRightOfLeftChild;
    node->leftChild = rightOfRightOfLeftChild;
    switch (rightOfLeftChild->balance)
    {
    case -1:
        deletedNodeLeftChild->balance = 0;
        node->balance = 1;
        break;
    case 0:
        deletedNodeLeftChild->balance = 0;
        node->balance = 0;
        break;
    case 1:
        deletedNodeLeftChild->balance = -1;
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
        }
        strcpy(node->value, value);
        *isClimb = false;
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

    if (node->balance == 0 || node->balance == 2 || node->balance == -2) // 1 или -1 - подъём продолжается
    {
        *isClimb = false;
    }

    return balance(node);
}

Tree *addValue(Tree *root, char *key, char *value, Error *errorCode)
{
    bool isClimb = true;
    return insert(root, key, value, &isClimb, errorCode);
}

Tree *findLeftBiggest(Tree *node)
{
    Tree *leftBiggestChild = node->leftChild;
    Tree *previousNode = NULL;
    while (leftBiggestChild->rightChild != NULL)
    {
        previousNode = leftBiggestChild;
        leftBiggestChild = leftBiggestChild->rightChild;
    }
    return leftBiggestChild;
}

Tree *deletePIZDEC(Tree *node, char *key, bool *isClimb)
{
    if (node == NULL)
    {
        *isClimb = false;
        return NULL;
    }

    int balanceDifference = 0;
    if (strcmp(key, node->key) == 0)
    {
        if (node->leftChild == NULL) // если слева нет ребенка - просто берем правого
        {                            // тут все норм с балансом, ничего не меняем (просто двигаем правую ветку на один вверх)
            Tree *freedNode = node;
            node = node->rightChild;
            free(freedNode->value);
            free(freedNode->key);
            free(freedNode);
            return node;
        }
        else // если слева есть ребенок - ищем максимального потомка слева и ставим на место удаляемого
        {
            Tree *nodeLeftBiggestChild = findLeftBiggest(node);
            strcpy(node->key, nodeLeftBiggestChild->key);
            strcpy(node->value, nodeLeftBiggestChild->value);
            node->leftChild = deletePIZDEC(node->leftChild, nodeLeftBiggestChild->key, isClimb);
            ++balanceDifference;
        }
    }
    else if (strcmp(key, node->key) < 0)
    {
        node->leftChild = deletePIZDEC(node->leftChild, key, isClimb);
        ++balanceDifference;
    }
    else
    {
        node->rightChild = deletePIZDEC(node->rightChild, key, isClimb);
        --balanceDifference;
    }

    if (!*isClimb)
    {
        return node;
    }
    node->balance += balanceDifference;

    if (node->balance != 0) // 0 - высота поддерева не изменилась, не 0 - изменилась
    {
        *isClimb = false;
    }

    return balance(node);
}

Tree *deleteValue(Tree *root, char *key)
{
    bool isClimb = true;
    return deletePIZDEC(root, key, &isClimb);
}

void printTree(Tree *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%s: %s %d| ", root->key, root->value, root->balance);
    printTree(root->leftChild);
    printTree(root->rightChild);
}

void freeTree(Tree *root)
{
    if (root == NULL)
    {
        return;
    }
    freeTree(root->leftChild);
    freeTree(root->rightChild);
    free(root->value);
    free(root->key);
    free(root);
}