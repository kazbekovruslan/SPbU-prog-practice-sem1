#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printArray(int *array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void swap(int *firstElement, int *secondElement)
{
    int transitElement = *firstElement;
    *firstElement = *secondElement;
    *secondElement = transitElement;
}

void selectionSort(int *array, int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        int minElementIndex = i;
        for (int j = i + 1; j < size; ++j)
        {
            if (array[j] < array[minElementIndex])
            {
                minElementIndex = j;
            }
        }
        if (minElementIndex != i)
        {
            swap(&array[i], &array[minElementIndex]);
        }
    }
}

bool test()
{
    int array[10] = { 32, 71, 12, 0, 1, 5, 10, 54, 21, 18};
    int sortedArray[10] = { 0, 1, 5, 10, 12, 18, 21, 32, 54, 71 };
    selectionSort(array, 10);
    for (int i = 0; i < 10; ++i)
    {
        if (array[i] != sortedArray[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    if (test())
    {
        printf("TEST PASSED!\n");
    }
    else
    {
        printf("TEST FAILED!\n");
    }
    int arrayLength = 0;
    int scanResult = 0;
    while (!scanResult)
    {
        printf("Enter the length of array for choose sort: ");
        scanResult = scanf("%d", &arrayLength);
        if (!scanResult)
        {
            printf("Numbers are required! Try again!");
            scanf("%*[^\n]");
        }
    }

    int *array = calloc(arrayLength, sizeof(int));
    if (array == NULL)
    {
        printf("Memory error!");
        return -1;
    }

    scanResult = 0;
    while (scanResult != arrayLength)
    {
        printf("Enter your array: ");
        for (int i = 0; i < arrayLength; ++i)
        {
            scanResult += scanf("%d", &array[i]);
        }
        if (scanResult != arrayLength)
        {
            printf("Numbers are required! You need to input %d elements! Try again!\n", arrayLength);
            scanf("%*[^\n]");
        }
    }

    selectionSort(array, arrayLength);
    printArray(array, arrayLength);
    
    return 0;
}