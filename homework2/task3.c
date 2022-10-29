#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define arraySize 100
#define countArraySize 1000

void bubbleSort(int* array, int arrayLength)
{
    int transitElement = 0;
    for (int i = 0; i < arrayLength; ++i)
    {
        for (int j = 0; j < arrayLength - 1 - i; ++j)
        {
            if (array[j] > array[j + 1])
            {
                transitElement = array[j];
                array[j] = array[j + 1];
                array[j + 1] = transitElement;
            }
        }
    }
}


void countSort(int* array, int arrayLength)
{
    int countArray[countArraySize] = { 0 };

    for (int i = 0; i < arrayLength; ++i)
    {
        ++countArray[array[i]];
    }

    int position = 0;
    for (int i = 0; i < countArraySize; ++i)
    {
        for (int j = 0; j < countArray[i]; ++j)
        {
            array[position] = i;
            ++position;
        }
    }
}


void main(void)
{
    int scanResult = 0;
    int arrayLength = 0;
    int array[arraySize] = { 0 };



    while (!scanResult || !(arrayLength > 0 && arrayLength < 100))
    {
        printf("Enter the array's length (<100): ");
        scanResult = scanf_s("%d", &arrayLength);
        if (!scanResult || !(arrayLength > 0 && arrayLength < 100))
        {
            printf("Incorrect input. Number (>0 and <100) is required. Try again!\n");
            scanf_s("%*[^\n]");
        }
    }

    bool wrongInput = false;
    scanResult = 0;
    while (scanResult < arrayLength || wrongInput)
    {
        scanResult = 0;
        wrongInput = false;
        printf("Enter the array (0 <= element < 1000): ");
        for (int i = 0; i < arrayLength; ++i)
        {
            scanResult += scanf_s("%d", &array[i]);
            if (array[i] < 0 || array[i] >= 1000)
            {
                wrongInput = true;
            }
        }
        if (scanResult < arrayLength || wrongInput)
        {
            printf("Incorrect input. Numbers (>=0 and <1000) are required. Try again!\n");
            scanf_s("%*[^\n]");
        }
    }



    int typeOfSort = 0;
    scanResult = 0;
    printf("What type of sorting do you want to use? ");
    while (!scanResult || !(typeOfSort >= 1 && typeOfSort <= 2))
    {
        printf("1 - Bubble Sort, 2 - Count Sort\nEnter here: ");
        scanResult = scanf_s("%d", &typeOfSort);
        if (!scanResult || !(typeOfSort >= 1 && typeOfSort <= 2))
        {
            printf("Incorrect input. Number is required. Try again!\n");
            scanf_s("%*[^\n]");
        }
    }

    if (typeOfSort == 1)
    {
        bubbleSort(array, arrayLength);
    }
    else
    {
        countSort(array, arrayLength);
    }

    for (int i = 0; i < arrayLength; ++i) printf("%d ", array[i]);
}