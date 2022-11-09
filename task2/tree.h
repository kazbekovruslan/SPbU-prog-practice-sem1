#pragma once
#include <stdio.h>

typedef int Error;

typedef struct Tree Tree;

//строит дерево разбора арифметического выражения по строчке
Error buildTree(Tree **root, FILE *file);

//вычисляет значение дерева разбора арифметического выражения
int calculateTree(Tree *root);

//выводит дерево
void printTree(Tree *root);

//очищает дерево
void freeTree(Tree **root);