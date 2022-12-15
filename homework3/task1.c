#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define arraySize 30

void swap(int *firstElement, int *secondElement)
{
    int transitElement = *firstElement;
    *firstElement = *secondElement;
    *secondElement = transitElement;
}

void printArray(int *array, int arrayLength)
{
    for (int i = 0; i < arrayLength; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int partition(int *array, int lowIndex, int highIndex)
{
    int pivot = array[lowIndex];
    int pivotIndex = lowIndex;

    int lastIndexOfPivot = 0;

    for (int i = lowIndex + 1; i <= highIndex; ++i)
    {
        if (array[i] < pivot)
        {
            swap(&array[i], &array[pivotIndex]);
            if (array[i] == pivot)
                lastIndexOfPivot = i;
            ++pivotIndex;
        }
    }

    if (array[pivotIndex] != pivot)
    {
        swap(&array[lastIndexOfPivot], &array[pivotIndex]);
    }

    return pivotIndex;
}

void insertSort(int *array, int lowIndex, int highIndex)
{
    int transitElement = 0;
    int shiftIndex = 0;
    for (int i = lowIndex + 1; i <= highIndex; ++i)
    {
        transitElement = array[i];
        shiftIndex = i - 1;
        while (shiftIndex >= 0 && transitElement < array[shiftIndex])
        {
            array[shiftIndex + 1] = array[shiftIndex];
            --shiftIndex;
        }
        array[shiftIndex + 1] = transitElement;
    }
}

void quickSort(int *array, int lowIndex, int highIndex)
{
    int pivotIndex = 0;
    if (lowIndex < highIndex)
    {
        if (highIndex - lowIndex >= 10)
        {
            pivotIndex = partition(array, lowIndex, highIndex);
            quickSort(array, lowIndex, pivotIndex - 1);
            quickSort(array, pivotIndex + 1, highIndex);
        }
        else
        {
            insertSort(array, lowIndex, highIndex);
        }
    }
}

// trying to commit with vscode

bool test()
{
    int arrayBeforeSort[30] = {70, 51, 5, 74, 24, 66, 45, 29, 59, 82, 21, 6, 5, 42, 60, 25, 56, 12, 21, 36, 32, 63, 11, 6, 82, 44, 58, 25, 16, 40};
    int arrayAfterSort[30] = {5, 5, 6, 6, 11, 12, 16, 21, 21, 24, 25, 25, 29, 32, 36, 40, 42, 44, 45, 51, 56, 58, 59, 60, 63, 66, 70, 74, 82, 82};
    quickSort(arrayBeforeSort, 0, 29);
    for (int i = 0; i < 30; ++i)
    {
        if (arrayBeforeSort[i] != arrayAfterSort[i])
        {
            return false;
        }
    }
    return true;
}

void main()
{
    if (test())
    {
        printf("TEST PASSED!\n");
    }
    else
    {
        printf("TEST FAILED!\n");
        return;
    }
    int array[arraySize] = {0};
    srand(time(0));

    for (int i = 0; i < arraySize; ++i)
    {
        array[i] = rand() % 84;
    }

    printf("Array before sort: ");
    printArray(array, arraySize);

    quickSort(array, 0, arraySize - 1);

    printf("\nArray  after sort: ");
    printArray(array, arraySize);
}
