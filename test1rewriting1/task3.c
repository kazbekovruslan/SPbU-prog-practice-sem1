#include <stdio.h>
#include <string.h>
#include <locale.h>

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("File not found!");
        return 1;
    }

    int frequence[255] = { 0 };
    while(!feof(file))
    {
        ++frequence[fgetc(file)];
    }
    fclose(file);

    for (int i = 0; i < 255; ++i)
    {
        if (frequence[i])
        {
            if ((char) i == '\n')
            {
                printf("Symbol (backslash)n: %d times\n", i, frequence[i]);
            }
            else
            {
                printf("Symbol %c: %d times\n", i, frequence[i]);
            }
        }
    }
    
    return 0;
}