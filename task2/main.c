#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"

int lastSurvivor(int amountOfSoldiers, int step)
{
    List *list = listCreate();
    if (list == NULL)
    {
        return -1;
    }

    int errorCode = 0;

    for (int i = 0; i < amountOfSoldiers; ++i)
    {
        errorCode = addNumber(list, i);
        if (errorCode != 0)
        {
            freeList(list);
            free(list);
            return errorCode;
        }
    }

    errorCode = removeNumbers(list, step);
    if (errorCode != 0)
    {
        freeList(list);
        free(list);
        return errorCode;
    }

    int lastStanding = 0;
    errorCode = firstElement(list, &lastStanding);
    if (errorCode != 0)
    {
        return errorCode; 
    }
    freeList(list);
    free(list);
    return lastStanding; //ошибки с "-", а номер >= 0, так что можем различать ошибку и ответ
}

bool test()
{
    return lastSurvivor(5, 2) == 2 && lastSurvivor(758, 43) == 24 && lastSurvivor(8, 1) == 7 && lastSurvivor(3, 7) == 2;
}

int main()
{
    if (!test())
    {
        printf("Tests failed!\n");
        return -1;
    }
    int scanResult = 0;
    int amountOfSoldiers = 0;
    while (!scanResult || amountOfSoldiers <= 0)
    {
        printf("Enter the amount of soldiers: ");
        scanResult = scanf("%d", &amountOfSoldiers);
        if (!scanResult || amountOfSoldiers <= 0)
        {
            printf("Incorrect input! Number (>0) is required. Try again!\n");
            scanf("%*[^\n]");
        }
    }

    scanResult = 0;
    int step = 0;
    while (!scanResult || step <= 0)
    {
        printf("Enter the step of killing the soldiers: ");
        scanResult = scanf("%d", &step);
        if (!scanResult || step <= 0)
        {
            printf("Incorrect input! Number (>0) is required. Try again!\n");
            scanf("%*[^\n]");
        }
    }

    if (lastSurvivor(amountOfSoldiers, step) != -1)
    {
        printf("Number of the last standing soldier is %d", lastSurvivor(amountOfSoldiers, step));
    }
    else
    {
        printf("Memory error!\n");
        return -1;
    }
    return 0;
}