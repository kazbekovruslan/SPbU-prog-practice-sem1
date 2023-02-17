#include <stdio.h>
#include "set.h"

void printError(char errorCode)
{
    switch (errorCode)
    {
    case MemoryAllocationError:
        printf("Memory allocation error!\n");
        break;
    case PointerIsNull:
        printf("Some given pointer is NULL!\n");
        break;
    }
}

int main()
{
    Error errorCode = OK;

    Set *firstSet = setCreate(&errorCode);
    if (errorCode != OK)
    {
        printError(errorCode);
        return errorCode;
    }

    int firstSetLength = 1;
    int scanResult = 0;
    while (!scanResult || firstSetLength <= 0)
    {
        printf("Enter the length of the first set: ");
        scanResult = scanf("%d", &firstSetLength);
        if (!scanResult)
        {
            printf("Incorrect input! Numbers are required!\n");
            scanf("%*[^\n]");
        }
        if (firstSetLength <= 0)
        {
            printf("Incorrect input! Length of set is positive!\n");
            scanf("%*[^\n]");
        }
    }

    printf("Enter the elements of first set: ");
    int enteredValue = 0;
    for (int i = 0; i < firstSetLength; ++i)
    {
        if (!scanf("%d", &enteredValue))
        {
            printf("Incorrect input! Numbers are required!\n");
            freeSet(firstSet);
            return -100;
        }

        errorCode = addValue(firstSet, enteredValue);
        if (errorCode != OK)
        {
            printError(errorCode);
            freeSet(firstSet);
            return errorCode;
        }
    }

    Set *secondSet = setCreate(&errorCode);
    if (errorCode != OK)
    {
        printError(errorCode);
        return errorCode;
    }

    int secondSetLength = 1;
    scanResult = 0;
    while (!scanResult || secondSetLength <= 0)
    {
        printf("Enter the length of the second set: ");
        scanResult = scanf("%d", &secondSetLength);
        if (!scanResult)
        {
            printf("Incorrect input! Numbers are required!\n");
            scanf("%*[^\n]");
        }
        if (secondSetLength <= 0)
        {
            printf("Incorrect input! Length of set is positive!\n");
            scanf("%*[^\n]");
        }
    }

    printf("Enter the elements of second set: ");
    for (int i = 0; i < secondSetLength; ++i)
    {
        if (!scanf("%d", &enteredValue))
        {
            printf("Incorrect input! Numbers are required!\n");
            freeSet(firstSet);
            freeSet(secondSet);
            return -100;
        }
        errorCode = addValue(secondSet, enteredValue);
        if (errorCode != OK)
        {
            printError(errorCode);
            freeSet(firstSet);
            freeSet(secondSet);
            return errorCode;
        }
    }

    Set *unionSet = setCreate(&errorCode);
    if (errorCode != OK)
    {
        printError(errorCode);
        freeSet(firstSet);
        freeSet(secondSet);
        return errorCode;
    }

    errorCode = setsUnion(firstSet, secondSet, unionSet);
    if (errorCode != OK)
    {
        printError(errorCode);
        freeSet(firstSet);
        freeSet(secondSet);
        freeSet(unionSet);
        return errorCode;
    }

    printf("Union of your sets: ");
    printSet(unionSet);

    freeSet(firstSet);
    freeSet(secondSet);
    freeSet(unionSet);
    return OK;
}