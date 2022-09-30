#include <stdio.h>
#include <stdlib.h>

#define arraySize 30

void swap(int *firstElement, int *secondElement)
{
    int transitElement = *firstElement;
    *firstElement = *secondElement;
    *secondElement = transitElement;
}


int partition(int *array, int low, int high)
{
    int transitElement = 0;
    int pivot = array[low];
    int pivotIndex = low;


    int lastIndexOfPivot = 0;

    for (int i = low + 1; i < high; ++i)
    {
        if (array[i] <= pivot)
        {
            swap(&array[i], &array[pivotIndex]);
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




void insertSort(int *array, int low, int high)
{
    int transitElement = 0;
    int j = 0;
    for (int i = low + 1; i < high; ++i)
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




void quickSort(int *array, int low, int high)
{
    int pivotIndex = 0;
    if (low < high) 
    {
        if (high - low < 10)
        {
            pivotIndex = partition(array, low, high);
            quickSort(array, low, pivotIndex);
            quickSort(array, pivotIndex + 1, high);
        }
        else
        {
            insertSort(array, low, high);
        }
    }
    
}






void main(void)
{
    int array[arraySize] = { 0 };
    for (int i = 0; i < arraySize; ++i)
    {
        array[i] = rand() % 84;
    }
    // долгий массив долго вводить, а тут нужно, чтобы длина была >20 для проверки работы partition
    
    printf("Array before sort: ");
    for (int i = 0; i < arraySize; ++i) printf("%d ", array[i]);
    
    quickSort(array, 0, arraySize);

    printf("\nArray  after sort: ");
    for (int i = 0; i < arraySize; ++i) printf("%d ", array[i]);
}
