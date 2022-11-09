#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

int main()
{
    List *list = listCreate();
    if (list == NULL)
    {
        printf("Memory error!\n");
        return -1;
    }
    printf("----SORTED LIST----\n");
    printf("Functions:\n");
    printf("0 - exit\n");
    printf("1 - add value to sorted list\n");
    printf("2 - remove value from list\n");
    printf("3 - print list\n");
    bool exitFlag = false;
    while (!exitFlag)
    {
        int function = 0;
        int scanResult = 0;
        Value value = 0;
        while (!scanResult || !(function >= 0 && function <= 3))
        {
            printf("\nEnter the number of the function (0 - 3): ");
            scanResult = scanf("%d", &function);
            if (!scanResult || !(function >= 0 && function <= 3))
            {
                printf("Incorrect input! Numbers 0 - 3 required. Try again!\n");
                scanf("%*[^\n]");
            }
        }
        switch (function)
        {
        case 1:
        {
            scanResult = 0;
            while (!scanResult)
            {
                printf("Enter the value you want to add to the list: ");
                scanResult = scanf("%d", &value);
                if (!scanResult)
                {
                    printf("Incorrect input! Numbers required. Try again!\n");
                    scanf("%*[^\n]");
                }
            }
            int errorCode = addValue(list, value);
            if (errorCode == -1)
            {
                printf("Memory error!\n");
                return -1;
            }
            break;
        }
        case 2:
        {
            scanResult = 0;
            while (!scanResult)
            {
                printf("Enter the value you want to remove from the list: ");
                scanResult = scanf("%d", &value);
                if (!scanResult)
                {
                    printf("Incorrect input! Numbers required. Try again!\n");
                    scanf("%*[^\n]");
                }
            }
            int errorCode = removeValue(list, value);
            if (errorCode == -1)
            {
                printf("Memory error!\n");
                return -1;
            }
            if (errorCode == -3)
            {
                printf("There is no such element!\n");
            }
            break;
        }
        case 3:
        {
            int errorCode = printList(list);
            if (errorCode == -1)
            {
                printf("Memory error!\n");
                return -1;
            }
            break;
        }
        case 0:
        {
            exitFlag = true;
            printf("Bye!\n");
            break;
        }
        }
    }
    freeList(list);
    free(list);
    return 0;
}