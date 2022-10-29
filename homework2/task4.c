#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define arraySize 10

void swap(int *firstElement, int *secondElement)
{
    int transitElement = *firstElement;
    *firstElement = *secondElement;
    *secondElement = transitElement;
}


void sort(int* array)
{
    int pivot = array[0];
    int currElement = 0;

    int pivotIndex = 0;

    for (int i = 1; i < arraySize; ++i)
    {
        if (array[i] < pivot)
        {
            swap(&array[i], &array[currElement]);
            if (array[i] == pivot) pivotIndex = i;
            ++currElement;
        }
    }

    if (array[currElement] != pivot)
    {
    swap(&array[pivotIndex], &array[currElement]);
    }
}

void main(void)
{
    int array[arraySize] = { 0 };

    srand(time(0));

    for (int i = 0; i < arraySize; ++i)
    {
        array[i] = rand() % 32;
    }
    printf("Array before: ");
    for (int i = 0; i < arraySize; ++i) printf("%d ", array[i]);
    sort(array);
    printf("\nArray  after: ");
    for (int i = 0; i < arraySize; ++i) printf("%d ", array[i]);
}