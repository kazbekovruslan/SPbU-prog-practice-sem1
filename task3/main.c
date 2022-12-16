#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../stack/stack.h"

#define maxLength 256

int operationPriority(char operation)
{
    if (operation == '+' || operation == '-')
    {
        return 1;
    }
    if (operation == '*' || operation == '/')
    {
        return 2;
    }
    return 3;
}

bool isOperation(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

void addChar(char *output, int *index, const char ch)
{
    output[(*index)++] = ch;
    output[(*index)++] = ' ';
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
    int topElement = 0;

    for (int i = 0; i < lengthOfSequence; ++i)
    {
        if (sequence[i] == '+' || sequence[i] == '-' || sequence[i] == '*' || sequence[i] == '/')
        {
            if (!isEmpty(stack))
            {
                if (errorCode = top(stack, &topElement) != 0)
                {
                    freeStack(stack);
                    return errorCode;
                }

                while (!isEmpty(stack) && operationPriority(topElement) >= operationPriority(sequence[i]))
                {
                    addChar(output, &outputIndex, topElement);
                    if (errorCode = pop(stack, &topElement) != 0)
                    {
                        freeStack(stack);
                        return errorCode;
                    }

                    if (!isEmpty(stack))
                    {
                        if (errorCode = top(stack, &topElement) != 0)
                        {
                            freeStack(stack);
                            return errorCode;
                        }
                    }
                }
            }

            if (errorCode = push(stack, sequence[i]) != 0)
            {
                freeStack(stack);
                return errorCode;
            }
        }

        else if (sequence[i] == '(')
        {
            if (errorCode = push(stack, sequence[i]) != 0)
            {
                freeStack(stack);
                return errorCode;
            }
        }

        else if (sequence[i] == ')')
        {
            if (isEmpty(stack))
            {
                freeStack(stack);
                return -1;
            }
            if (errorCode = top(stack, &topElement) != 0)
            {
                freeStack(stack);
                return errorCode;
            }
            while (!isEmpty(stack) && topElement != '(')
            {
                addChar(output, &outputIndex, topElement);
                if (errorCode = pop(stack, &topElement) != 0)
                {
                    freeStack(stack);
                    return errorCode;
                }
                if (errorCode = top(stack, &topElement) != 0)
                {
                    freeStack(stack);
                    return errorCode;
                }
            }
            if (isEmpty(stack))
            {
                freeStack(stack);
                return -1;
            }
            if (errorCode = pop(stack, &topElement) != 0)
            {
                freeStack(stack);
                return errorCode;
            }
        }

        else if ((int)sequence[i] >= 48 && (int)sequence[i] <= 57) // == digit (in our case == number)
        {
            addChar(output, &outputIndex, sequence[i]);
        }

        else if (sequence[i] == ' ')
        {
            continue;
        }

        else
        {
            freeStack(stack);
            return -5; // wrong input
        }
    }

    topElement = 0;
    while (!isEmpty(stack))
    {
        if (errorCode = pop(stack, &topElement) != 0 || !isOperation(topElement))
        {
            freeStack(stack);
            return errorCode;
        }
        addChar(output, &outputIndex, topElement);
    }
    freeStack(stack);
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