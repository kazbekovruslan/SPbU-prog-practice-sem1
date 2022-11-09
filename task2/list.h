#pragma once
#include <stdbool.h>

typedef int Error;

typedef struct List List;

//создает пустой список и возвращает его
List *listCreate();

//добавляет значение в список так, чтобы он был циклическим
//возвращает -1 из-за ошибок с памятью и если список NULL
Error addNumber(List *list, int number);

//удаляет значение из циклического списка
//возвращает -1 из-за ошибок с памятью и если список NULL
Error removeNumbers(List *list, int step);

//выводит циклический список
//возвращает -1, если список NULL
Error printList(List *list);

//возвращает true если длина списка 1 и false в противном случае
bool isLength1(List *list);

//записывает в lastStanding значение первого элемента списка
//возвращает -1, если список NULL или если голова NULL
Error firstElement(List *list, int *lastStanding);

//очищает циклический список
//возвращает -1, если список NULL
Error freeList(List *list);