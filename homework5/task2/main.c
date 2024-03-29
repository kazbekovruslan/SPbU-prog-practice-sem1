#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../stack/stack.h"

int areBracketsBalanced(char *sequence, bool *areBalanced)
{
    Stack *stack = stackCreate();
    if (stack == NULL)
    {
        return -1;
    }

    int errorCode = 0;
    int lengthOfSequence = strlen(sequence);

    int topElement = 0;
    int poppedElement = 0;

    for (int i = 0; i < lengthOfSequence; ++i)
    {
        switch (sequence[i])
        {
        case '(':
        case '{':
        case '[':
        {
            errorCode = push(stack, sequence[i]);
            if (errorCode != 0)
            {
                freeStack(stack);
                return errorCode;
            }
            break;
        }
        case ')':
        {
            errorCode = top(stack, &topElement);
            if (errorCode == -2)
            {
                *areBalanced = false;
                freeStack(stack);
                return 0;
            }
            if (errorCode != 0)
            {
                freeStack(stack);
                return errorCode;
            }

            if (topElement == (int)'(')
            {
                errorCode = pop(stack, &poppedElement);
                if (errorCode != 0)
                {
                    freeStack(stack);
                    return errorCode;
                }
            }
            else
            {
                *areBalanced = false;
                freeStack(stack);
                return 0;
            }
            break;
        }
        case '}':
        {
            errorCode = top(stack, &topElement);
            if (errorCode == -1)
            {
                freeStack(stack);
                return -1;
            }
            if (errorCode == -2)
            {
                *areBalanced = false;
                freeStack(stack);
                return 0;
            }

            if (topElement == (int)'{')
            {
                errorCode = pop(stack, &poppedElement);
                if (errorCode != 0)
                {
                    freeStack(stack);
                    return errorCode;
                }
            }
            else
            {
                *areBalanced = false;
                freeStack(stack);
                return 0;
            }
            break;
        }
        case ']':
        {
            errorCode = top(stack, &topElement);
            if (errorCode == -1)
            {
                freeStack(stack);
                return -1;
            }
            if (errorCode == -2)
            {
                *areBalanced = false;
                freeStack(stack);
                return 0;
            }

            if (topElement == (int)'[')
            {
                errorCode = pop(stack, &poppedElement);
                if (errorCode != 0)
                {
                    freeStack(stack);
                    return errorCode;
                }
            }
            else
            {
                *areBalanced = false;
                freeStack(stack);
                return 0;
            }
            break;
        }
        }
    }

    *areBalanced = isEmpty(stack);
    freeStack(stack);
    return 0;
}

bool test1()
{
    char sequence[10] = "([({dd})])";
    bool areBalanced = false;
    int errorCode = areBracketsBalanced(sequence, &areBalanced);
    if (errorCode != 0 || !areBalanced)
    {
        return false;
    }
    return true;
}

bool test2()
{
    char sequence[15] = "{([}])";
    bool areBalanced = false;
    int errorCode = areBracketsBalanced(sequence, &areBalanced);
    if (errorCode != 0 || areBalanced)
    {
        return false;
    }
    return true;
}

bool test3()
{
    char sequence[5] = "[{})]";
    bool areBalanced = false;
    int errorCode = areBracketsBalanced(sequence, &areBalanced);
    if (errorCode != 0 || areBalanced)
    {
        return false;
    }
    return true;
}

int main()
{
    if (test1() && test2() && test3())
    {
        printf("Tests passed!\n");
    }
    else
    {
        printf("Tests failed!\n");
        return -10;
    }
    int lengthOfSequence = -1;
    int scanareBalanced = 0;

    while (!scanareBalanced || lengthOfSequence <= 0)
    {
        printf("Enter the length of your sequence: ");
        scanareBalanced = scanf("%d", &lengthOfSequence);
        if (!scanareBalanced)
        {
            scanf("%*[^\n]");
            printf("Incorrect input! Number is required. Try again!\n");
        }
        else if (lengthOfSequence <= 0)
        {
            scanf("%*[^\n]");
            printf("Incorrect input! Length of sequence is positive. Try again!\n");
        }
    }

    char *sequence = calloc(lengthOfSequence + 1, sizeof(char));
    if (sequence == NULL)
    {
        printf("Memory error!\n");
        return -1;
    }
    printf("Enter the sequence you want to check for balance of brackets: ");
    scanf("%s", sequence);
    if (sequence[lengthOfSequence] != '\0')
    {
        printf("Length of your sequence doesn't match with inputted length!");
        return -1;
    }

    bool areBalanced = false;
    int errorCode = areBracketsBalanced(sequence, &areBalanced);
    free(sequence);
    if (errorCode == -1)
    {
        printf("Memory error!\n");
        return -1;
    }
    if (errorCode == -2)
    {
        printf("Stack elements error!\n");
        return -2;
    }

    if (areBalanced)
    {
        printf("Brackets in your sequence are balanced!\n");
    }
    else
    {
        printf("Brackets in your sequence are NOT balanced!\n");
    }

    return 0;
}