#pragma once

typedef int Error;

typedef struct Tree Tree;

Tree *insert(Tree *node, char *key, char *value, bool *isClimb, Error *errorCode);

// get value by key. If there is no such key, it returns NULL
char *findValueByKey(Tree *node, char *key);

// print tree with preorder
void printTree(Tree *root);

// free all tree
void freeTree(Tree **root);