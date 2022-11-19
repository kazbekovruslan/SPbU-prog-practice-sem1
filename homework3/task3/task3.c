#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


#define arraySize 15
#define countArraySize 30

void printArray(int *array, int arrayLength)
{
    for (int i = 0; i < arrayLength; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int mostFrequent(int *array, int arrayLength)
{
    int mostFrequentNumber = array[0];
    int counter = 1;
    int maxCounter = 1;
    for (int i = 0; i < arraySize - 1; ++i)
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
            counter = 1;
        }
    }

    return mostFrequentNumber;
}

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

bool test()
{
    int array[15] = { 4, 10, 15, 2, 10, 5, 20, 10, 19, 11, 29, 8, 15, 21, 16 };
    quickSort(array, 0, 15);
    if (mostFrequent(array, 15) == 10)
    {
        return true;
    }
    return false;
}

void main(void)
{
    if (test())
    {
        printf("TEST PASSED!\n");
    }
    else
    {
        printf("TEST FAILED!\n");
    }
    int array[arraySize] = { 0 };
    srand(time(0));
    
    for (int i = 0; i < arraySize; ++i) array[i] = rand() % countArraySize;
    
    printf("Your COMMON array: ");
    printArray(array, arraySize);

    quickSort(array, 0, arraySize);

    printf("\nYour SORTED array: ");
    printArray(array, arraySize);

    printf("\nThe most frequent number in the array is %d", mostFrequent(array, arraySize));
}