#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

Error sum(List *list, Index index1, Index index2)
{
    if (list == NULL)
    {
        return PointerIsNull;
    }
    int firstSummand = 0;
    int secondSummand = 0;
    int errorCode = removeValue(list, index1, &firstSummand);

    if (errorCode == ZeroElementsInList)
    {
        return LessThanTwoElementsInList;
    }
    if (errorCode != OK)
    {
        return errorCode;
    }

    if (index1 < index2)
    {
        errorCode = removeValue(list, index2 - 1, &secondSummand);
        if (errorCode == ZeroElementsInList)
        {
            return LessThanTwoElementsInList;
        }
        if (errorCode != OK)
        {
            return errorCode;
        }
    }
    else
    {
        errorCode = removeValue(list, index2, &secondSummand);
        if (errorCode == ZeroElementsInList)
        {
            return LessThanTwoElementsInList;
        }
        if (errorCode != OK)
        {
            return errorCode;
        }
    }
    errorCode = addValue(list, firstSummand + secondSummand);
    return errorCode;
}

void printFunctions()
{
    printf("Functions:\n");
    printf("0 - exit\n");
    printf("1 - add element value with *\n");
    printf("2 - remove element with number *\n");
    printf("3 - pop 2 elements with indexes * and * and add their sum to list\n");
    printf("4 - print list\n");
    printf("5 - print list of functions\n");
}

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
    case ZeroElementsInList:
        printf("There no elements in list!\n");
        break;
    case LessThanTwoElementsInList:
        printf("There are less than 2 elements in list!\n");
        break;
    case NoSuchIndex:
        printf("There is no such index in list!\n");
        break;
    }
}

int main()
{
    List *list = NULL;
    if (listCreate(&list) == MemoryAllocationError)
    {
        printf("Memory allocation error!\n");
        return MemoryAllocationError;
    }

    printf("---SORTED LIST---\n");
    printFunctions();
    bool exitFlag = false;
    int errorCode = 0;
    while (!exitFlag)
    {
        int scanResult = 0;
        int function = -1;
        while (!scanResult || !(function >= 0 && function <= 5))
        {
            printf("Enter the function: ");
            scanResult = scanf("%d", &function);
            if (!scanResult || !(function >= 0 && function <= 5))
            {
                printf("Incorrect input!\n");
                scanf("%*[^\n]");
            }
        }

        switch (function)
        {
        case 0:
            printf("Bye!\n");
            exitFlag = true;
            break;
        case 1:
            int value = 0;
            scanResult = 0;
            while (!scanResult)
            {
                printf("Enter the value: ");
                scanResult = scanf("%d", &value);
                if (!scanResult)
                {
                    printf("Incorrect input!\n");
                    scanf("%*[^\n]");
                }
            }

            errorCode = addValue(list, value);
            if (errorCode != OK)
            {
                printError(errorCode);
                return errorCode;
            }
            printf("Success!\n");
            break;
        case 2:
            int index = 0;
            scanResult = 0;
            while (!scanResult)
            {
                printf("Enter the index: ");
                scanResult = scanf("%d", &index);
                if (!scanResult)
                {
                    printf("Incorrect input!\n");
                    scanf("%*[^\n]");
                }
            }

            int deletedValue = 0;
            errorCode = removeValue(list, index, &deletedValue);
            if (errorCode != OK)
            {
                printError(errorCode);
                return errorCode;
            }
            printf("Deleted element - %d\n", deletedValue);
            break;
        case 3:
            scanResult = 0;
            int index1 = 0;
            int index2 = 0;
            while (scanResult < 2 || (index1 == index2))
            {
                printf("Enter the indexes: ");
                scanResult += scanf("%d %d", &index1, &index2);
                if (scanResult < 2 || (index1 == index2))
                {
                    printf("Incorrect input! Indexes should be different!\n");
                    scanf("%*[^\n]");
                }
            }
            errorCode = sum(list, index1, index2);
            if (errorCode != OK)
            {
                printError(errorCode);
                return errorCode;
            }
            printf("Success!\n");
            break;
        case 4:
            printList(list);
            break;
        case 5:
            printFunctions();
            break;
        }
    }
    freeList(list);
    return OK;
}