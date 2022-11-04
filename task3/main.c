#include <stdio.h>
#include <stdlib.h>
#include "mergeList.h"

int main()
{
    List *head = NULL;
    int errorCode = fillList(&head, "input.txt");
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