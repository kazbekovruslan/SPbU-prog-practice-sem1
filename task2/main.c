#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int lastSurvivor(int amountOfSoldiers, int step)
{
    List *list = listCreate();
    if (list == NULL)
    {
        return -1;
    }

    for (int i = 0; i < amountOfSoldiers; ++i)
    {
        addNumber(list, i);
    }

    removeNumbers(list, step);

    return lastElement(list);
}

int main()
{
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