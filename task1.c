#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define arraySize 50

void printArray(int *array, int arrayLength)
{
    for (int i = 0; i < arrayLength; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}


void insertSort(int *array, int arrayLength)
{
    int transitElement = 0;
    int j = 0;
    for (int i = 1; i < arrayLength; ++i)
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

// void swap(int *firstElement, int *secondElement)
// {
//     int transitElement = *firstElement;
//     *firstElement = *secondElement;
//     *secondElement = transitElement;
// }

// void insertSort1(int *array, int arrayLength)
// {
//     int transitElement = 0;
//     int j = 0;
//     for (int i = 1; i < arrayLength; ++i)
//     {
//         transitElement = array[i];
//         j = i - 1;
//         if (array[i] % 2 == 0)
//         {
//             if (array[j] % 2 == 0)
//             {
//                 while (j >= 0 && transitElement < array[j])
//                 {
//                     array[j + 1] = array[j];
//                     --j;
//                 }
//                 array[j+1] = transitElement;
//             }
//             else
//             {
//                 swap(&array[i], &array[--j]);
//                 --j;
//                 while (j >= 0 && transitElement < array[j])
//                 {
//                     array[j + 1] = array[j];
//                     --j;
//                 }
//                 array[j+1] = transitElement;
//             }
//         }
//         printArray(array, arrayLength);
//     }
// }

void newInsertSort(int *array, int arrayLength)
{
    int tmpArray[arraySize] = { 0 };
    for (int i = 0; i < arraySize; ++i) tmpArray[i] = 1000;
    int last = 0;
    for (int i = 0; i < arrayLength; ++i)
    {
        if (array[i] % 2 == 0)
        {
            tmpArray[i] = array[i];
            last = i;
        }
    }
    insertSort(tmpArray, last + 1);
    int j = 0;
    for (int i = 0; i < arrayLength; ++i)
    {
        if (array[i] % 2 == 0)
        {
            array[i] = tmpArray[j++];
        }
    }
}

int test()
{
    int arrayBefore[5] = { 6, 4, 3, 2, 1 };
    newInsertSort(arrayBefore, 5);
    int arrayAfter[5] = { 2, 4, 3, 6, 1};
    for (int i = 0; i < 5; ++i)
    {
        if (arrayBefore[i] != arrayAfter[i])
        {
            printf("TEST FAILED!\n");
            return -1;
        }
    }

    int arrayBefore1[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    newInsertSort(arrayBefore1, 10);
    int arrayAfter1[10] = { 2, 9, 4, 7, 6, 5, 8, 3, 10, 1};
    for (int i = 0; i < 10; ++i)
    {
        if (arrayBefore1[i] != arrayAfter1[i])
        {
            printf("TEST FAILED1!\n");
            return -1;
        }
    }
    printf("TEST PASSED\n");
}


void main(void)
{
    test();

    int array[arraySize] = { 0 };
    int arrayLength = 0;
    int scanResult = 0;

    while (!scanResult)
    {
        printf("Enter the array's length: ");
        scanResult = scanf_s("%d", &arrayLength);
        if (!scanResult)
        {
            printf("Incorrect input. Number is required. Try again!\n");
            scanf_s("%*[^\n]");
        }
    }

    scanResult = 0;
    while (scanResult < arrayLength)
    {
        scanResult = 0;
        printf("Enter the array: ");
        for (int i = 0; i < arrayLength; ++i)
        {
            scanResult += scanf("%d", &array[i]);
        }
        if (scanResult < arrayLength)
        {
            printf("Incorrect input. Numbers are required. Try again!\n");
            scanf_s("%*[^\n]");
        }
    }


    newInsertSort(array, arrayLength);
    printf("Your sorted array: ");
    printArray(array, arrayLength);
}