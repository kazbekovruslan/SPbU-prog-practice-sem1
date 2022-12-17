#pragma once

typedef int Error;

typedef struct List List;

// добавление элемента(записи) в список
// возвращает -1 если список NULL или не выделилась память
Error addRecord(List **head, char *name, char *phone);

// очищает список
void freeList(List **head);

// выводит список
void printList(List *head);

// сортировка слиянием
void mergeSort(List **head, int typeOfCompare);