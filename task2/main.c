#include <stdio.h>
#include <stdbool.h>

#include "stack.h"

void printFunctions()
{
    printf("Functions:\n");
    printf("0 - exit\n");
    printf("1 - push\n");
    printf("2 - pop\n");
    printf("3 - add\n");
    printf("4 - print stack\n");
    printf("5 - print list of functions\n");
}

int main()
{
    Stack *stack = NULL;
    if (stackCreate(&stack) == MemoryAllocationError)
    {
        printf("Memory allocation error!\n");
        return MemoryAllocationError;
    }

    printf("---STACK---\n");
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
                    scanf("%d*[^\n]");
                }
            }

            errorCode = push(stack, value);
            if (errorCode != OK)
            {
                printf("Error - %d\n", errorCode);
                return errorCode;
            }
            printf("Success!\n");
            break;
        case 2:
            int poppedValue = 0;
            errorCode = pop(stack, &poppedValue);
            if (errorCode != OK)
            {
                printf("Error - %d\n", errorCode);
                return errorCode;
            }
            printf("Popped value - %d\n", poppedValue);
            break;
        case 3:
            errorCode = add(stack);
            if (errorCode != OK)
            {
                printf("Error - %d\n", errorCode);
                return errorCode;
            }
            printf("Success!\n");
            break;
        case 4:
            printStack(stack);
            break;
        case 5:
            printFunctions();
            break;
        }
    }
    freeStack(stack);
    return OK;
}