#include <stdio.h>
#include <stdlib.h>


#define arraySize 10

void sort(int* array)
{
    int transitElement = 0;
    int pivot = array[0];
    int pivotIndex = 0;


    int lastIndexOfPivot = 0;

    for (int i = 1; i < arraySize; ++i)
    {
        if (array[i] <= pivot)
        {
            transitElement = array[i];
            array[i] = array[pivotIndex];
            array[pivotIndex] = transitElement;
            lastIndexOfPivot = i;
            ++pivotIndex;
        }
    }

    if (array[pivotIndex] != pivot)
    {
    transitElement = array[lastIndexOfPivot];
    array[lastIndexOfPivot] = array[pivotIndex];
    array[pivotIndex] = transitElement;
    }

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