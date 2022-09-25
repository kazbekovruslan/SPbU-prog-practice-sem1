#include <stdio.h>
#include <stdlib.h>


#define arraySize 10

void sort(int* array)
{
    int transitElement = 0;
    int pivot = array[0];
    int index = 0;

    for (int i = 1; i < arraySize; ++i)
    {
        if (array[i] < pivot)
        {
            transitElement = array[i];
            array[i] = array[index];
            array[index] = transitElement;
            ++index;
        }
    }

    transitElement = pivot;
    pivot = array[index];
    array[index] = transitElement;
}    

void main(void)
{

    int array[arraySize] = { 0 };
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