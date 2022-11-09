#pragma once

typedef int Error;

typedef struct List List;

//заполняет список значениями из файла
//возвращает -1 если список NULL
//возвращает -2 если не нашелся файл
Error fillList(List **head, char *pathToFile);

//очищает список
void freeList(List **head);

//выводит список
void printList(List *head);

//сравнивает два элемента списка по типу
int compare(List *left, List *right, int typeOfCompare);

//делит список на 2 примерно равных списка
void split(List *sourceList, List **leftList, List **rightList);

//собирает 2 списка в 1
void merge(List *leftList, List *rightList, List **resultList, int typeOfCompare);

//сортировка слиянием
void mergeSort(List **head, int typeOfCompare);