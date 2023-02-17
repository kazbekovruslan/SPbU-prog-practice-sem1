#pragma once

typedef int Error;
typedef int Value;

typedef struct List List;

// создает пустой список и возвращает его
List *listCreate();

// добавляет значение в список так, чтобы он был сортированным
// возвращает -1 из-за ошибок с памятью и если список NULL
Error addValue(List *list, int value);

// удаляет значение из сортированного списка
// возвращает -1 из-за ошибок с памятью и если список NULL
//-2 если голова списка пустая
//-3 если нет такого элемента
Error removeValue(List *list, int value);

// выводит список
// возвращает -1 из-за ошибок с памятью и если список NULL
Error printList(List *list);

// очищает список
// возвращает -1, если список NULL
Error freeList(List *list);

// тесты функций добавления и удаления
bool tests();