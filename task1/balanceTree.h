#pragma once

typedef int Error;

typedef enum
{
    MemoryAllocationError = -1,
    OK = 0
} Errors;

typedef struct Tree Tree;

// возвращает значение по ключу. Если нет такого ключа - возвращает NULL
char *findValueByKey(Tree *node, char *key);

// добавляет значение по ключу. Если уже есть такой ключ - меняет значение
// принимает на вход переменную errorCode, в которой хранится код ошибки (OK - 0, MemoryAllocationError - -1)
Tree *addValue(Tree *root, char *key, char *value, Error *errorCode);

// удаляет значение по ключу. Если нет такого ключа - ничего не делает
Tree *deleteValue(Tree *root, char *key);

// выводит дерево с обходом в глубину
void printTree(Tree *root);

// очищает память под дерево
void freeTree(Tree *root);