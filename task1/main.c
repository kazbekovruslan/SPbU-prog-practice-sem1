#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "tree.h"

#define maxLength

typedef enum
{
    MemoryAllocationError = -1,
    OK = 0
} Errors;

int main()
{
    printf("---DICTIONARY---\n");
    printf("Functions:\n");
    printf("0 - exit\n");
    printf("1 - add value to the dictionary by key\n");
    printf("2 - get value from the dictionary by key\n");
    printf("3 - check value for being in the dictionary by key\n");
    printf("4 - delete key and its value\n");
    printf("5 - print tree in preorder\n");
    Tree *root = NULL;
    bool exitFlag = false;
    while (!exitFlag)
    {
        int function = 0;
        int scanResult = 0;
        while (!scanResult || !(function >= 0 && function <= 5))
        {
            printf("\nEnter the number of the function (0 - 5): ");
            scanResult = scanf("%d", &function);
            if (!scanResult || !(function >= 0 && function <= 5))
            {
                printf("Incorrect input! Numbers 0 - 5 required. Try again!\n");
                scanf("%*[^\n]");
            }
        }

        char value[maxLength] = {0};
        int key = 0;
        switch (function)
        {
        case 1: //добавить значение по заданному ключу в словарь
        {
            scanResult = 0;
            while (!scanResult)
            {
                printf("Enter the key for the value you want to add to the dictionary: ");
                scanResult = scanf("%d", &key);
                if (!scanResult)
                {
                    printf("Incorrect input! Number required. Try again!\n");
                    scanf("%*[^\n]");
                }
            }
            printf("Enter the value you want to add: ");
            scanf("%s", value);

            int errorCode = addValue(&root, value, key);
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
            scanResult = 0;
            while (!scanResult)
            {
                printf("Enter the key for the value you want to get from the dictionary: ");
                scanResult = scanf("%d", &key);
                if (!scanResult)
                {
                    printf("Incorrect input! Number required. Try again!\n");
                    scanf("%*[^\n]");
                }
            }
            printf("Value for your key: %s\n", findValueByKey(root, key));
            break;
        }
        case 3: //проверить наличие заданного ключа в словаре
        {
            scanResult = 0;
            while (!scanResult)
            {
                printf("Enter the key for the value you want to check for being in the dictionary: ");
                scanResult = scanf("%d", &key);
                if (!scanResult)
                {
                    printf("Incorrect input! Number required. Try again!\n");
                    scanf("%*[^\n]");
                }
            }
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
            scanResult = 0;
            while (!scanResult)
            {
                printf("Enter the key for the value you want to delete from the dictionary: ");
                scanResult = scanf("%d", &key);
                if (!scanResult)
                {
                    printf("Incorrect input! Number required. Try again!\n");
                    scanf("%*[^\n]");
                }
            }
            deleteValue(&root, key);
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
        case 0:
        {
            exitFlag = true;
            printf("Bye!\n");
            break;
        }
        }
    }
    freeTree(&root);
    return 0;
}