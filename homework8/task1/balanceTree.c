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
        return findValueByKey(node->leftChild, key);
    }
    else if (strcmp(key, node->key) > 0)
    {
        return findValueByKey(node->rightChild, key);
    }
    else
    {
        return node->value;
    }
}

Tree *rotateLeft(Tree *node)
{
    Tree *movedNodeRightChild = node->rightChild;
    Tree *leftOfRightChild = movedNodeRightChild->leftChild;
    movedNodeRightChild->leftChild = node;
    node->rightChild = leftOfRightChild;
    if (movedNodeRightChild->balance == 0)
    {
        movedNodeRightChild->balance = -1;
        node->balance = 1;
    }
    else
    {
        movedNodeRightChild->balance = 0;
        node->balance = 0;
    }
    return movedNodeRightChild;
}

Tree *rotateRight(Tree *node)
{
    Tree *movedNodeLeftChild = node->leftChild;
    Tree *rightOfLeftChild = movedNodeLeftChild->rightChild;
    movedNodeLeftChild->rightChild = node;
    node->leftChild = rightOfLeftChild;
    if (movedNodeLeftChild->balance == 0)
    {
        movedNodeLeftChild->balance = 1;
        node->balance = -1;
    }
    else
    {
        movedNodeLeftChild->balance = 0;
        node->balance = 0;
    }
    return movedNodeLeftChild;
}

Tree *bigRotateLeft(Tree *node)
{
    Tree *movedNodeRightChild = node->rightChild;
    Tree *leftOfRightChild = movedNodeRightChild->leftChild;
    Tree *leftOfLeftOfRightChild = leftOfRightChild->leftChild;
    Tree *rightOfLeftOfRightChild = leftOfRightChild->rightChild;
    leftOfRightChild->leftChild = node;
    leftOfRightChild->rightChild = movedNodeRightChild;
    node->rightChild = leftOfLeftOfRightChild;
    movedNodeRightChild->leftChild = rightOfLeftOfRightChild;
    switch (leftOfRightChild->balance)
    {
    case -1:
        movedNodeRightChild->balance = 1;
        node->balance = 0;
        break;
    case 0:
        movedNodeRightChild->balance = 0;
        node->balance = 0;
        break;
    case 1:
        movedNodeRightChild->balance = 0;
        node->balance = -1;
        break;
    }
    leftOfRightChild->balance = 0;
    return leftOfRightChild;
}

Tree *bigRotateRight(Tree *node)
{
    Tree *movedNodeLeftChild = node->leftChild;
    Tree *rightOfLeftChild = movedNodeLeftChild->rightChild;
    Tree *leftOfRightOfLeftChild = rightOfLeftChild->leftChild;
    Tree *rightOfRightOfLeftChild = rightOfLeftChild->rightChild;
    rightOfLeftChild->leftChild = movedNodeLeftChild;
    rightOfLeftChild->rightChild = node;
    movedNodeLeftChild->rightChild = leftOfRightOfLeftChild;
    node->leftChild = rightOfRightOfLeftChild;
    switch (rightOfLeftChild->balance)
    {
    case -1:
        movedNodeLeftChild->balance = 0;
        node->balance = 1;
        break;
    case 0:
        movedNodeLeftChild->balance = 0;
        node->balance = 0;
        break;
    case 1:
        movedNodeLeftChild->balance = -1;
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
    if (newNode == NULL)
    {
        return NULL;
    }
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
        balanceDifference = -1;
    }
    else
    {
        node->rightChild = insert(node->rightChild, key, value, isClimb, errorCode);
        balanceDifference = 1;
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

Tree *removeValue(Tree *node, char *key, bool *isClimb)
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
            node->leftChild = removeValue(node->leftChild, nodeLeftBiggestChild->key, isClimb);
            balanceDifference = 1;
        }
    }
    else if (strcmp(key, node->key) < 0)
    {
        node->leftChild = removeValue(node->leftChild, key, isClimb);
        balanceDifference = 1;
    }
    else
    {
        node->rightChild = removeValue(node->rightChild, key, isClimb);
        balanceDifference = -1;
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
    return removeValue(root, key, &isClimb);
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