#pragma once

typedef int Error;

typedef struct List List;

// добавление элемента(записи) в список
// возвращает -1 если список NULL или не выделилась память
Error addRecord(List **head, char *name, int amount);

// очищает список
void freeList(List **head);

// выводит список
void printList(List *head);

// выводит список до конкретного индекса
// возвращает -3, если индекс некорректный
Error printListUpIndex(List *head, int index);

// сортировка слиянием
void mergeSort(List **head, int typeOfCompare);