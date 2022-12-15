#include <stdio.h>
#include <stdlib.h>
#include "qsort.h"

int mostFrequent(int *array, int arrayLength)
{
    quickSort(array, 0, arrayLength - 1);
    int mostFrequentNumber = array[0];
    int counter = 1;
    int maxCounter = 1;
    for (int i = 0; i < arrayLength - 1; ++i)
    {
        if (array[i] == array[i + 1])
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
    FILE *file = fopen("../../homework4/task2/input.txt", "r");
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
    fseek(file, 0, SEEK_SET);

    if (sizeOfArray == 0)
    {
        printf("Incorrect data!\n");
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
    int scanResult = 0;
    for (int i = 0; i < sizeOfArray; ++i)
    {
        scanResult = fscanf(file, "%d", &array[i]);
        if (scanResult != 1)
        {
            printf("Incorrect data. File should contain only numbers!\n");
            fclose(file);
            free(array);
            return -2;
        }
        printf("%d ", array[i]);
    }
    fclose(file);

    printf("\nThe most frequent number in the array is %d", mostFrequent(array, sizeOfArray));
    free(array);
    return 0;
}