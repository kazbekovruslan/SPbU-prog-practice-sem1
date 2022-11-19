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
    quickSort(array, 0, arrayLength - 1);
    int mostFrequentNumber = array[0];
    int counter = 1;
    int maxCounter = 1;
    for (int i = 0; i < arrayLength - 1; ++i)
    {
        if (array[i] == array[i + 1])
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

bool test()
{
    int array[15] = {4, 10, 15, 2, 10, 5, 20, 10, 19, 11, 29, 8, 15, 21, 16};
    quickSort(array, 0, 14);
    if (mostFrequent(array, 15) == 10)
    {
        return true;
    }
    return false;
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
    int array[arraySize] = {0};

    srand(time(0));
    for (int i = 0; i < arraySize; ++i)
    {
        array[i] = rand() % countArraySize;
    }
    printf("Your array: ");
    printArray(array, arraySize);

    printf("The most frequent number in the array is %d", mostFrequent(array, arraySize));
}