#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mergeList.h"

#define maxLength 256

Error fillList(List **head, char *pathToFile)
{
    if (head == NULL)
    {
        return -1;
    }
    FILE *file = fopen(pathToFile, "r");
    if (file == NULL)
    {
        return -2;
    }
    int errorCode = 0;
    while (!feof(file))
    {
        char name[maxLength] = {0};
        char phone[maxLength] = {0};
        fscanf(file, "%s %s", name, phone);
        errorCode = addRecord(head, name, phone);
        if (errorCode != 0)
        {
            return errorCode;
        }
    }
    return 0;
}

int main()
{
    if (!tests())
    {
        printf("TESTS FAILED!\n");
        return -100;
    }
    List *head = NULL;
    int errorCode = fillList(&head, "../../task3/input.txt");
    if (errorCode == -1)
    {
        printf("Memory error!\n");
    }
    if (errorCode == -2)
    {
        printf("There is no file!\n");
        return -2;
    }
    int typeOfCompare = 0; // 0 - name, 1 - phone
    int scanResult = 0;
    while (!scanResult || !(typeOfCompare >= 0 && typeOfCompare <= 1))
    {
        printf("Enter the type of compare for your phonebook (0 - name, 1 - phone): ");
        scanResult = scanf("%d", &typeOfCompare);
        if (!scanResult || !(typeOfCompare >= 0 && typeOfCompare <= 1))
        {
            printf("Incorrect input! Number 0 or 1 is required. Try again!\n");
            scanf("%*[^\n]");
        }
    }

    mergeSort(&head, typeOfCompare);
    printList(head);
    freeList(&head);
    return 0;
}