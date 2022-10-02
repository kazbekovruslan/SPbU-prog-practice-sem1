#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define arraySize 100

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
        if (highIndex - lowIndex < 10)
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


bool binarySearch(int *array, int number, int lowIndex, int highIndex)
{
    int mid = (highIndex + lowIndex) / 2;
    if (highIndex < lowIndex)
    {
        return false;
    }
    if (array[mid] == number)
    {
        return true;
    }
    if (array[mid] < number)
    {
        binarySearch(array, number, mid + 1, highIndex);
    }
    else
    {
        binarySearch(array, number, lowIndex, mid - 1);
    }
}



void main(void)
{
    int arrayLength = -1;
    int amountOfNumbers = -1;
    int array[arraySize] = { 0 };
    
    int scanResult = 0;

    while (!scanResult || arrayLength <= 0)
    {
        printf("Enter the array's length (<100): ");
        scanResult = scanf("%d", &arrayLength);
        if (!scanResult)
        {
            printf("Incorrect input. Number is required. Try again!\n");
            scanf("%*[^\n]");
        }
        if (scanResult && arrayLength <= 0)
        {
            printf("Amount of numbers in array is positive. Try again!\n");
            scanf("%*[^\n]");
        }
    }

    srand(time(0));
    for (int i = 0; i < arrayLength; ++i) array[i] = rand() % 31;


    printf("Your array: ");
    quickSort(array, 0, arrayLength);
    for (int i = 0; i < arrayLength; ++i) printf("%d ", array[i]);

    printf("\n");

    scanResult = 0;
    while (!scanResult || amountOfNumbers <= 0)
    {
        printf("Enter the amount of numbers you want to find in the array: ");
        scanResult = scanf("%d", &amountOfNumbers);
        if (!scanResult)
        {
            printf("Incorrect input. Number is required. Try again!\n");
            scanf("%*[^\n]");
        }
        if (scanResult && amountOfNumbers <= 0)
        {
            printf("Amount of numbers you want to find in the array is positive. Try again!\n");
            scanf("%*[^\n]");
        }
        
    }

    printf("\n");
    
    int number = 0;

    for (int i = 0; i < amountOfNumbers; ++i)
    {
        number = rand() % 31;
        if (binarySearch(array, number, 0, arrayLength - 1))
        {
            printf("Number %d is contained in the array! :)\n", number);
        }
        else
        {
            printf("Number %d isn't contained in the array! :(\n", number);
        }
    }
}