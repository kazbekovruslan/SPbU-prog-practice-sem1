#pragma once

typedef char Error;
typedef int Value;
typedef int Index;

typedef enum
{
    OK = 0,
    MemoryAllocationError = -1,
    PointerIsNull = -2,
    ZeroElementsInList = -3,
    LessThanTwoElementsInList = -4,
    NoSuchIndex = -5
} Errors;

typedef struct List List;

// создает пустой список и возвращает его
Error listCreate(List **list);

// добавляет значение в список так, чтобы он был сортированным
Error addValue(List *list, Value value);

// удаляет значение из сортированного списка
Error removeValue(List *list, Index index, Value *deletedValue);

// выводит список
Error printList(List *list);

// очищает список
Error freeList(List *list);