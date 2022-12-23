#pragma once

typedef int Value;

typedef enum
{
    OK = 0,
    MemoryAllocationError = -1,
    PointerIsNull = -2,
} Error;

typedef struct Set Set;

// создает пустое множество и возвращает его
Set *setCreate(Error *errorCode);

// добавляет значение в множество
Error addValue(Set *set, Value value);

// добавляет в множество unionSet объединение двух множеств - firstSet и secondSet
Error setsUnion(Set *firstSet, Set *secondSet, Set *unionSet);

// выводит множество
Error printSet(Set *set);

// очищает множество
Error freeSet(Set *set);