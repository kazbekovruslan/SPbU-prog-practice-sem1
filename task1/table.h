#pragma once
#include "list.h"

typedef int Error;

typedef struct Table Table;

//хеш-функция: возвращает хеш из диапазона от 0 до hashSize
int hash(char *key);

//добавляет слово в хеш таблицу
//возвращает код ошибки из Errors
Error addToTable(Table *table, char *word);

//возвращает коэффициент заполнения хеш таблицы
float loadFactor(Table *table);

//возвращает максимальную длину списка из хеш таблицы
int maxLengthList(Table *table);

//возвращает среднюю длину списка из хеш таблицы
int averageLengthList(Table *table);

//выводит хеш таблицу
void printTable(Table *table);

//очищает хеш таблицу
void freeTable(Table *table);