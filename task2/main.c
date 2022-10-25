#include <stdio.h>
#include <stdlib.h>
#include "../stack/stack.h"

bool areBracketsBalanced(char *sequence, int lengthOfSequence)
{
    Stack *stack = stackCreate();

    int errorCode = 0;

    for (int i = 0; i < lengthOfSequence; ++i)
    {
        switch (sequence[i])
        {
            case '(':
            case '{':
            case '[':
            {
                errorCode = push(stack, sequence[i]);
                if (errorCode == -1)
                {
                    printf("Memory error!\n");
                    return -1;
                }
                break;
            }
            case ')':
            {
                if (errorCode = top(stack) == (int)'(')
                {
                    if (errorCode == -2)
                    {
                        return false;
                    }
                    pop(stack);
                }
                else
                {
                    return false;
                }
                break;
            }
            case '}':
            {
                if (errorCode = top(stack) == (int)'{')
                {
                    if (errorCode == -2)
                    {
                        return false;
                    }
                    pop(stack);
                }
                else
                {
                    return false;
                }
                break;
            }
            case ']':
            {
                if (errorCode = top(stack) == (int)'[')
                {
                    if (errorCode == -2)
                    {
                        return false;
                    }
                    pop(stack);
                }
                else
                {
                    return false;
                }
                break;
            }
        }
    }
    return len(stack) == 0;
}

int main()
{
    int lengthOfSequence = -1;
    int scanResult = 0;

    while (!scanResult || lengthOfSequence <= 0)
    {
        printf("Enter the length of your sequence: ");
        scanResult = scanf("%d", &lengthOfSequence);
        if (!scanResult)
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
    
    if (areBracketsBalanced(sequence, lengthOfSequence))
    {
        printf("Brackets in your sequence are balanced!\n");
    }
    else
    {
        printf("Brackets in your sequence are NOT balanced!\n");
    }

    return 0;
}