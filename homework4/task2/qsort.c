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

    for (int i = lowIndex + 1; i < highIndex; ++i)
    {
        if (array[i] <= pivot)
        {
            swap(&array[i], &array[pivotIndex]);
            if (array[i] == pivot) lastIndexOfPivot = i;
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
    int j = 0;
    for (int i = lowIndex + 1; i < highIndex; ++i)
    {
        transitElement = array[i];
        j = i - 1;
        while (j >= 0 && transitElement < array[j])
        {
            array[j + 1] = array[j];
            --j;
        }
        array[j+1] = transitElement;
    }
}




void quickSort(int *array, int lowIndex, int highIndex)
{
    int pivotIndex = 0;
    if (lowIndex < highIndex) 
    {
        if (highIndex - lowIndex > 10)
        {
            pivotIndex = partition(array, lowIndex, highIndex);
            quickSort(array, lowIndex, pivotIndex);
            quickSort(array, pivotIndex + 1, highIndex);
        }
        else
        {
            insertSort(array, lowIndex, highIndex);
        }
    }
}