#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define arraySize 10
#define countArraySize 100

int count(int *array, int arrayLength)
{
    int countArray[countArraySize] = { 0 };

    for (int i = 0; i < arrayLength; ++i)
    {
        ++countArray[array[i]];
    }

    int maxAmount = 0;
    int mostFrequentNumber = 0;
    for (int i = 0; i < countArraySize; ++i)
    {
        if (countArray[i] > maxAmount)
        {
            maxAmount = countArray[i];
            mostFrequentNumber = i;
        }
    }
    return mostFrequentNumber;
}

void main(void)
{
    int array[arraySize] = { 0 };
    srand(time(0));
    
    for (int i = 0; i < arraySize; ++i) array[i] = rand() % countArraySize;
    
    printf("Your array: ");
    for (int i = 0; i < arraySize; ++i) printf("%d ", array[i]);

    printf("\nThe most frequent number in the array is %d", count(array, arraySize));
}