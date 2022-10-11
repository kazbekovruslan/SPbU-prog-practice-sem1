#include <stdio.h>
#include <stdlib.h>
#include "qsort.h"


int count(int *array, int arrayLength)
{
    quickSort(array, 0, arrayLength);
    int mostFrequentNumber = array[0];
    int counter = 1;
    int maxCounter = 1;
    for (int i = 0; i < arrayLength - 1; ++i)
    {
        if (array[i] == array[i+1])
        {
            ++counter;
            if (counter > maxCounter)
            {
                mostFrequentNumber = array[i];
                maxCounter = counter;
            }
        }
        else
        {
            counter == 1;
        }
    }

    return mostFrequentNumber;
}




int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("File not found!");
        return 1;
    }

    int sizeOfArray = 0;
    int tmp = 0;
    while (fscanf(file, "%d", &tmp) == 1)
    {
        ++sizeOfArray;
    }
    fseek(file, 0L, SEEK_SET); 
    
    if (sizeOfArray == 0)
    {
        printf("File is empty!");
        fclose(file);
        return 1;
    }
    int *array = calloc(sizeOfArray, sizeof(int));
    if (array == NULL)
    {
        printf("Memory error!");
        fclose(file);
        return 1;
    }

    printf("Your array: ");
    for (int i = 0; i < sizeOfArray; ++i)
    {
        fscanf(file, "%d", &array[i]);
        printf("%d ", array[i]);
    }
    fclose(file);

    printf("\nThe most frequent number in the array is %d", count(array, sizeOfArray));
    free(array);
    return 0;
}