#include <stdio.h>
#include <stdlib.h>

void printToConsole(char character, int counter)
{
    if (counter == 1)
    {
        printf("%c", character);
    }
    else
    {
        printf("%d%c", counter, character);
    }
}

int main(void)
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("File not found!\n");
        return -1;
    }

    char firstCharacter = fgetc(file);
    char secondCharacter = 0;
    int counter = 1;

    while (!feof(file))
    {
        secondCharacter = fgetc(file);
        if (firstCharacter == secondCharacter)
        {
            ++counter;
        }
        else
        {
            printToConsole(firstCharacter, counter);
            counter = 1;
        }
        firstCharacter = secondCharacter;
    }
    return 0;
}