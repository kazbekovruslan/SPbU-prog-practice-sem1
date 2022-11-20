#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "balanceTree.h"

#define maxLength

typedef int Error;

typedef enum
{
    MemoryAllocationError = -1,
    OK = 0
} Errors;

void printFunctions()
{
    printf("Functions:\n");
    printf("0 - exit\n");
    printf("1 - add value to the dictionary by key\n");
    printf("2 - get value from the dictionary by key\n");
    printf("3 - check value for being in the dictionary by key\n");
    printf("4 - delete key and its value\n");
    printf("5 - print tree in preorder\n");
    printf("6 - print list of functions\n");
}

int main()
{
    printf("---DICTIONARY---\n");
    printFunctions();
    Tree *root = NULL;
    bool exitFlag = false;
    while (!exitFlag)
    {
        int function = 0;
        int scanResult = 0;
        while (!scanResult || !(function >= 0 && function <= 6))
        {
            printf("\nEnter the number of the function (0 - 6): ");
            scanResult = scanf("%d", &function);
            if (!scanResult || !(function >= 0 && function <= 5))
            {
                printf("Incorrect input! Numbers 0 - 6 required. Try again!\n");
                scanf("%*[^\n]");
            }
        }

        char value[maxLength] = {0};
        char key[maxLength] = {0};
        switch (function)
        {
        case 1: //добавить значение по заданному ключу в словарь
        {
            printf("Enter the key for the value you want to add to the dictionary: ");
            scanf("%s", key);
            printf("Enter the value you want to add: ");
            scanf("%s", value);

            Error errorCode = OK;
            addValue(root, key, value, &errorCode);
            if (errorCode == MemoryAllocationError)
            {
                printf("Memory error!\n");
                return -1;
            }
            printf("Value added successfully!\n");
            break;
        }
        case 2: //получить значение по заданному ключу из словаря
        {
            printf("Enter the key for the value you want to get from the dictionary: ");
            scanf("%s", key);
            printf("Value for your key: %s\n", findValueByKey(root, key));
            break;
        }
        case 3: //проверить наличие заданного ключа в словаре
        {
            printf("Enter the key for the value you want to check for being in the dictionary: ");
            scanf("%s", key);
            if (findValueByKey(root, key) != NULL)
            {
                printf("Value is in the dictionary!\n");
                break;
            }
            printf("Value is NOT in the dictionary!\n");
            break;
        }
        case 4: //удалить заданный ключ и связанное с ним значение из словаря
        {
            printf("Enter the key for the value you want to delete from the dictionary: ");
            scanf("%s", key);
            deleteValue(root, key);
            printf("Value deleted successfully!\n");
            break;
        }
        case 5:
        {
            printf("Dictionary (key: value): ");
            printTree(root);
            printf("\n");
            break;
        }
        case 6:
        {
            printFunctions();
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
    freeTree(root);
    return 0;
}