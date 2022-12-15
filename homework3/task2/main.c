#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../quickSort/quickSort.h"

#define arraySize 100

void printArray(int *array, int arrayLength)
{
    for (int i = 0; i < arrayLength; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

bool binarySearchInSortedArray(int *array, int number, int lowIndex, int highIndex)
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
    else if (array[mid] < number)
    {
        binarySearchInSortedArray(array, number, mid + 1, highIndex);
    }
    else
    {
        binarySearchInSortedArray(array, number, lowIndex, mid - 1);
    }
}

bool test()
{
    int array[10] = {4, 5, 10, 3, 5, 15, 32, 1, -2, 61};
    quickSort(array, 0, 9);
    printArray(array, 10);
    for (int i = 0; i < 10; ++i)
    {
        if (binarySearchInSortedArray(array, array[i], 0, 9) != true)
        {
            return false;
        }
    }
    if (binarySearchInSortedArray(array, 6, 0, 9) || binarySearchInSortedArray(array, -3, 0, 9) || binarySearchInSortedArray(array, 70, 0, 9))
    {
        return false;
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
    int arrayLength = -1;
    int amountOfNumbers = -1;
    int array[arraySize] = {0};

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
    for (int i = 0; i < arrayLength; ++i)
    {
        array[i] = rand() % 31;
    }

    printf("Your array: ");
    printArray(array, arrayLength);

    quickSort(array, 0, arrayLength);

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

    int number = 0;

    for (int i = 0; i < amountOfNumbers; ++i)
    {
        number = rand() % 31;
        if (binarySearchInSortedArray(array, number, 0, arrayLength - 1))
        {
            printf("Number %d is contained in the array! :)\n", number);
        }
        else
        {
            printf("Number %d isn't contained in the array! :(\n", number);
        }
    }
}