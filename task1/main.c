#include <stdio.h>
#include <stdlib.h>
#include "../stack/stack.h"

int operation(Stack *stack, char typeOfOperation)
{
    int errorCode = 0;

    int secondElement = 0;
    errorCode = pop(stack, &secondElement);
    if (errorCode == -1 || errorCode == -2)
    {
        return errorCode;
    }

    int firstElement = 0;
    errorCode = pop(stack, &firstElement);
    if (errorCode == -1 || errorCode == -2)
    {
        return errorCode;
    }


    switch (typeOfOperation)
    {
        case '+':
        {
            errorCode = push(stack, firstElement + secondElement);
            break;
        }
        case '-':
        {
            errorCode = push(stack, firstElement - secondElement);
            break;
        }
        case '*':
        {
            errorCode = push(stack, firstElement * secondElement);
            break;
        }
        case '/':
        {
            errorCode = push(stack, firstElement / secondElement);
            break;
        }
    }
    return errorCode;
}



int main()
{
    Stack *stack = stackCreate();
    if (stack == NULL)
    {
        printf("Memory error!\n");
        return -1;
    }
    int errorCode = 0;


    printf("Enter your arithmetic expression in postfix form (numbers only 0-9): ");
    for (char c = getc(stdin); c != '\n'; c = getc(stdin))
    {
        if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            errorCode = operation(stack, c);
            if (errorCode == -1)
            {
                printf("Memory error!\n");
                freeStack(stack);
                free(stack);
                return -1;
            }
            if (errorCode == -2)
            {
                printf("Stack elements error!\n");
                freeStack(stack);
                free(stack);
                return -2;
            }
        }
        else if ((int)c >= 48 && (int)c <= 57)
        {
            int number = c - '0';
            errorCode = push(stack, number);
            if (errorCode == -1)
            {
                printf("Memory error!\n");
                freeStack(stack);
                free(stack);
                return -1;
            }
            if (errorCode == -2)
            {
                printf("Stack elements error!\n");
                freeStack(stack);
                free(stack);
                return -2;
            }
        }
        else if (c == ' ')
        {
        }
        else
        {
            printf("Incorrect input. Input only '+', '-', '*', '/' and numbers 0 - 9\n");
            return -1;
        }
    }
    
    int answer = 0;
    errorCode = pop(stack, &answer);
    if (errorCode == -1)
    {
        printf("Memory error!\n");
        freeStack(stack);
        free(stack);
        return -1;
    }
    if (errorCode == -2)
    {
        printf("Stack elements error!\n");
        freeStack(stack);
        free(stack);
        return -2;
    }

    freeStack(stack);
    free(stack);

    printf("Answer: %d", answer);
    return 0;
}