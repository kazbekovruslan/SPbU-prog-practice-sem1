#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../stack/stack.h"

#define maxLength 256

int operationPriority (char operation)
{
    if (operation == '+' || operation == '-')
    {
        return 1;
    }
    if (operation == '*' || operation == '/')
    {
        return 2;
    }
    return 0;
}

void addChar(char *output, int *index, const char ch) {
    output[(*index)++] = ch;
}

int sortingStation(const char *sequence, const int lengthOfSequence, char *output)
{
    Stack *stack = stackCreate();
    if (stack == NULL)
    {
        return -1;
    }

    int errorCode = 0;
    int outputIndex = 0;

    for (int i = 0; i < lengthOfSequence; ++i)
    {
        if (sequence[i] == '+' || sequence[i] == '-' || sequence[i] == '*' || sequence[i] == '/')
        {
            int topElement = 0;
            errorCode = top(stack, &topElement);
            if (errorCode == -1)
            {
                freeStack(stack);
                free(stack);
                return -1;
            }
            while (operationPriority(topElement) >= operationPriority(sequence[i]))
            {
                addChar(output, &outputIndex, sequence[i]);
            }
            errorCode = push(stack, sequence[i]);
            if (errorCode == -1)
            {
                freeStack(stack);
                free(stack);
                return -1;
            }
        }
        else if (sequence[i] == '(')
        {
            errorCode = push(stack, sequence[i]);
            if (errorCode == -1)
            {
                freeStack(stack);
                free(stack);
                return -1;
            }
        }
        else if (sequence[i] == ')')
        {
            int topElement = 0;
            errorCode = top(stack, &topElement);
            if (errorCode == -1)
            {
                freeStack(stack);
                free(stack);
                return -1;
            }
            if (errorCode == -2)
            {
                freeStack(stack);
                free(stack);
                return -2;
            }
            while (topElement != '(')
            {
                int poppedElement = 0;
                errorCode = pop(stack, &poppedElement);
                if (errorCode == -1)
                {
                    freeStack(stack);
                    free(stack);
                    return -1;
                }
                if (errorCode == -2)
                {
                    freeStack(stack);
                    free(stack);
                    return -3;
                }

                int topElement = 0; //new top element
                errorCode = top(stack, &topElement);
                if (errorCode == -1)
                {
                    freeStack(stack);
                    free(stack);
                    return -1;
                }
                if (errorCode == -2)
                {
                    freeStack(stack);
                    free(stack);
                    return -3;
                }
                addChar(output, &outputIndex, poppedElement);
            }

            int poppedElement = 0; // opened bracket
            errorCode = pop(stack, &poppedElement);
            if (errorCode == -1)
            {
                freeStack(stack);
                free(stack);
                return -1;
            }
            if (errorCode == -2)
            {
                freeStack(stack);
                free(stack);
                return -2;
            }
        }
        else if ((int)sequence[i] >= 48 && (int)sequence[i] <= 57) // == digit (in our case == number)
        {
            addChar(output, &outputIndex, sequence[i]);
        }
        else if (sequence[i] == ' ')
        {
        }
        else
        {
            freeStack(stack);
            free(stack);
            return -5; //wrong input
        }
    }
    int lengthOfStack = 0;
    errorCode = len(stack, &lengthOfStack);
    if (errorCode == -1)
    {
        freeStack(stack);
        free(stack);
        return -1;
    }
    for (int i = 0; i < lengthOfStack; ++i)
    {
        int poppedElement = 0;
        errorCode = pop(stack, &poppedElement);
        if (errorCode == -1)
        {
            freeStack(stack);
            free(stack);
            return -1;
        }
        if (errorCode == -2)
        {
            freeStack(stack);
            free(stack);
            return -2;
        }
        addChar(output, &outputIndex, poppedElement);
    }
    return 0;
}

int main()
{
    char sequence[maxLength] = "";
    printf("Enter your arithmetic expression in infix form (numbers only 0-9, length < 256): ");
    gets(sequence);

    char output[maxLength] = "";

    int errorCode = sortingStation(sequence, strlen(sequence), output);
    if (errorCode == -1)
    {
        printf("Memory error!\n");
        return -1;
    }
    else if (errorCode == -2)
    {
        printf("Stack elements error!\n");
        return -2;
    }
    else if (errorCode == -3)
    {
        printf("Missing bracket!\n");
        return -3;
    }
    else if (errorCode == -5)
    {
        printf("Incorrect input. Input only '+', '-', '*', '/', '(', ')' and numbers 0 - 9\n");
        return -5;
    }
    printf("Your arithmetic expression in postfix form: %s", output);

    return 0;
}