#include <stdio.h>
#include <stdbool.h>

#define maxLength 256

bool doesFitThePattern(char *string)
{
    int state = 0;
    int currentChar = -1;
    int iterator = 0;
    while (currentChar != '\0')
    {
        currentChar = string[iterator++];
        switch (state)
        {
        case 0:
            if ((currentChar >= 'A' && currentChar <= 'Z') || (currentChar >= 'a' && currentChar <= 'z'))
            {
                state = 1;
                break;
            }
            return false;
        case 1:
            if ((currentChar >= 'A' && currentChar <= 'Z') || (currentChar >= 'a' && currentChar <= 'z') ||
                (currentChar >= '0' && currentChar <= '9') || (currentChar == '_'))
            {
                state = 1;
                break;
            }
            return currentChar == '\0';
        }
    }
}

int main()
{
    char string[maxLength] = {0};
    printf("Enter the string you want to check for pattern [A-Za-z] ([A-Za-z] | [0-9] | _ )*: ");
    scanf("%s", string);

    if (doesFitThePattern(string))
    {
        printf("%s fits the pattern!\n", string);
    }
    else
    {
        printf("%s doesn't fit the pattern!\n", string);
    }
    return 0;
}