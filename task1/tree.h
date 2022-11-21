#pragma once

typedef int Error;

typedef struct Tree Tree;

// add value by key. If there is such key, new value replace old value
// OK - no error (return 0), MemoryAllocationError - it's clear :) (return -1)
Error addValue(Tree **root, char *value, int key);

// get value by key. If there is no such key, it returns NULL
char *findValueByKey(Tree *root, int key);

// delete key and its value. If there is no such key, nothing happens
void deleteValue(Tree **root, int key);

// print tree with preorder
void printTree(Tree *root);

// free all tree
void freeTree(Tree **root);