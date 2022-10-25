#include <stdio.h>
#include <stdlib.h>
#include "../stack/stack.h"

int operation(Stack *stack, char typeOfOperation)
{
    int errorCode = 0;
    int secondElement = pop(stack);
    int firstElement = pop(stack);
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
    int errorCode = 0;

    printf("Enter your arithmetic expression in postfix form (numbers only 0-9): ");
    for (char c = getc(stdin); c != '\n'; c = getc(stdin))
    {
        if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            errorCode = operation(stack, c);
            if (errorCode != 0)
            {
                printf("Memory error!\n");
                freeStack(stack);
                free(stack);
                return -1;
            }
        }
        else if ((int)c >= 48 && (int)c <= 57)
        {
            int number = c - '0';
            errorCode = push(stack, number);
            if (errorCode != 0)
            {
                printf("Memory error!\n");
                freeStack(stack);
                free(stack);
                return -1;
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

    printf("Answer: %d", pop(stack));
    return 0;
}