#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int *firstElement, int *secondElement)
{
    int transitElement = *firstElement;
    *firstElement = *secondElement;
    *secondElement = transitElement;
}

void printArray(int *array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int elementsPermutation(int *array, int arrayLength)
{
    int counterOfPermutations = 0;
    int j = 0;
    for (int i = 0; i < arrayLength; ++i)
    {
        if (array[i] % 2 == 0)
        {
            if (array[i - 1] % 2 == 0 || i == 0)
            {
                ++j;
            }
            else
            {
                swap(&array[i], &array[j++]);
                ++counterOfPermutations;
            }
        }
    }
    return counterOfPermutations;
}

bool test1(void)
{
    int arrayBeforePermutations[5] = {2, 1, 3, 4, 5};
    int arrayAfterPermutations[5] = {2, 4, 3, 1, 5};
    elementsPermutation(arrayBeforePermutations, 5);
    for (int i = 0; i < 5; ++i)
    {
        if (arrayAfterPermutations[i] != arrayBeforePermutations[i])
        {
            return false;
        }
    }
    return true;
}

bool test2(void)
{
    int arrayBeforePermutations[5] = {2, 4, 3, 1, 5};
    int arrayAfterPermutations[5] = {2, 4, 3, 1, 5};
    int countOfPermutations = elementsPermutation(arrayBeforePermutations, 5);
    if (countOfPermutations == 0)
    {
        return true;
    }
    return false;
}

int main(void)
{
    if (!test1())
    {
        printf("Test 1 FAILED!\n");
        return -1;
    }
    if (!test2())
    {
        printf("Test 2 FAILED!\n");
        return -2;
    }

    int scanResult = 0;
    int arrayLength = 0;
    while (!scanResult || arrayLength < 1)
    {
        printf("Enter the length of the array: ");
        scanResult = scanf("%d", &arrayLength);
        if (!scanResult || arrayLength < 1)
        {
            printf("Incorrect input! Number > 0 is required. Try again!\n");
            scanf("%*[^\n]");
        }
    }

    int *array = calloc(arrayLength, sizeof(int));
    scanResult = 0;
    while (scanResult != arrayLength)
    {
        scanResult = 0;
        printf("Enter your array with length %d: ", arrayLength);
        for (int i = 0; i < arrayLength; ++i)
        {
            scanResult += scanf("%d", &array[i]);
        }
        if (scanResult != arrayLength)
        {
            printf("Incorrect input! Numbers are required. Try again!\n");
            scanf("%*[^\n]");
        }
    }

    elementsPermutation(array, arrayLength);
    printf("Your new array: ");
    printArray(array, arrayLength);
    free(array);
    return 0;
}