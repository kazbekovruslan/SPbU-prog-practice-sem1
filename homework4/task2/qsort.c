#include "qsort.h"

void swap(int *firstElement, int *secondElement)
{
    int transitElement = *firstElement;
    *firstElement = *secondElement;
    *secondElement = transitElement;
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