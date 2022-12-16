#pragma once

typedef int Error;

typedef struct List List;

// заполняет список значениями из файла
// возвращает -1 если список NULL
// возвращает -2 если не нашелся файл
Error fillList(List **head, char *pathToFile);

// очищает список
void freeList(List **head);

// выводит список
void printList(List *head);

// сортировка слиянием
void mergeSort(List **head, int typeOfCompare);