#include <stdio.h>
#include <stdlib.h>
#include "mergeList.h"

#define maxLength 256

void printError(int errorCode)
{
    switch (errorCode)
    {
    case 0:
        break;
    case -1:
        printf("Memory error!\n");
        break;
    case -2:
        printf("File not found!\n");
        break;
    }
}

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

    int amount = 0;
    while (!feof(file))
    {
        char name[maxLength] = {0};
        char currentCharacter = 0;
        int iterator = -1;
        while (currentCharacter != '-')
        {
            currentCharacter = getc(file);
            if (currentCharacter == '\n')
            {
                continue;
            }
            name[++iterator] = currentCharacter;
        }
        name[iterator] = '\0';
        fscanf(file, "%d", &amount);
        errorCode = addRecord(head, name, amount);
        if (errorCode != 0)
        {
            return errorCode;
        }
    }
    fclose(file);
    return 0;
}

int main()
{
    int scanResult = 0;
    int discount50Percent = 0;
    int discount25Percent = 0;

    while (!scanResult)
    {
        printf("Enter the amount of goods for 50%% discount and for 25%% discount: ");
        scanResult = scanf("%d%d", &discount50Percent, &discount25Percent);
        if (!scanResult)
        {
            printf("Incorrect input! There should be only numbers!\n");
            scanf("%*[^\n]");
        }
    }

    List *head = NULL;
    int errorCode = fillList(&head, "../../task2/storage.txt");
    printError(errorCode);

    printList(head);
    printFirstPart(&head, discount50Percent);

    printSecondPart(&head, discount25Percent);

    printRemainingPart(&head);

    freeList(&head);
    return 0;
}