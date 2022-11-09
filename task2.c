#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void swap(int *firstElement, int *secondElement)
{
    int transitElement = *firstElement;
    *firstElement = *secondElement;
    *secondElement = transitElement;
}

void printArray(int *array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

bool isSorted(int *array, int arrayLength)
{
    for (int i = 0; i < arrayLength - 1; ++i)
    {
        if (array[i] > array[i + 1])
        {
            return false;
        }
    }
    return true;
}

void shuffle(int *array, int arrayLength)
{
    srand(time(0));
    for (int i = 0; i < arrayLength; ++i)
    {
        swap(&array[i], &array[rand() % arrayLength]);
    }
}

void bogosort(int *array, int arrayLength)
{
    int iterationCounter = 0;
    while (!isSorted(array, arrayLength))
    {
        if (iterationCounter % 10000000 == 0)
        {
            printf("Processing... :)\n");
        }
        shuffle(array, arrayLength);
        ++iterationCounter;
    }
}

int main(void)
{
    int scanResult = 0;
    int arrayLength = 0;
    while (!scanResult || arrayLength < 1)
    {
        printf("Enter the length of the array: ");
        scanResult = scanf("%d", &arrayLength);
        if (!scanResult || arrayLength < 1)
        {
            printf("Incorrect input! Number > 0 is required. Try again!\n");
            scanf("%*[^\n]");
        }
    }

    int *array = calloc(arrayLength, sizeof(int));
    scanResult = 0;
    while (scanResult != arrayLength)
    {
        scanResult = 0;
        printf("Enter your array with length %d: ", arrayLength);
        for (int i = 0; i < arrayLength; ++i)
        {
            scanResult += scanf("%d", &array[i]);
        }
        if (scanResult != arrayLength)
        {
            printf("Incorrect input! Numbers are required. Try again!\n");
            scanf("%*[^\n]");
        }
    }

    bogosort(array, arrayLength);
    printf("Sorted array: ");
    printArray(array, arrayLength);
    free(array);
    return 0;
}