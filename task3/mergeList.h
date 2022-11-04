#pragma once
#include <stdbool.h>

typedef int Error;

typedef struct List List;

Error fillList(List **head, char *pathToFile);

void freeList(List **head);

void printList(List *head);

int compare(List *left, List *right, int typeOfCompare);

void split(List *sourceList, List **leftList, List **rightList);

void merge(List *leftList, List *rightList, List **resultList, int typeOfCompare);

void mergeSort(List **head, int typeOfCompare);