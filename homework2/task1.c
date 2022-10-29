#include <stdio.h>
#include <stdbool.h>

int recursiveFibonacciNumber(int number)
{
    if (number < 3)
    {
        return 1;
    }
    else
    {
        return recursiveFibonacciNumber(number - 1) + recursiveFibonacciNumber(number - 2);
    }
}
//при n >= 39 уже очень заметно

int iterativeFibonacciNumber(int number)
{
    int queueOfTwoNumbers[2] = { 1, 1 };
    int currentFibonacciNumber = 1;
    for (int i = 2; i < number; ++i)
    {
        currentFibonacciNumber = queueOfTwoNumbers[0] + queueOfTwoNumbers[1];
        queueOfTwoNumbers[0] = queueOfTwoNumbers[1];
        queueOfTwoNumbers[1] = currentFibonacciNumber;
    }
    return currentFibonacciNumber;
}

bool test1(void)
{
    for (int i = 0; i < 35; ++i)
    {
        if (recursiveFibonacciNumber(i) != iterativeFibonacciNumber(i))
        {
            return false;
        }
    }
    return true;
}

bool test2(void)
{
    return recursiveFibonacciNumber(36) != 14930352 || iterativeFibonacciNumber(36) != 14930352;
}

bool test3(void)
{
    return recursiveFibonacciNumber(2) != 1 || iterativeFibonacciNumber(2) != 1;
}

void main(void)
{
    if (!test1() || !test2() || !test3())
    {
        printf("ERROR! TESTS FAILED! \n");
        return;
    }

    int number = 0;
    int scanResult = 0;

    while (!scanResult || number <= 0)
    {
        printf("Enter the number of the Fibonacci number: ");
        scanResult = scanf_s("%d", &number);
        if (!scanResult)
        {
            printf("Incorrect input. Number is required. Try again!\n");
            scanf_s("%*[^\n]");
        }
        if (number <= 0 && scanResult)
        {
            printf("Number can only be positive. Try again!\n");
        }
    }

    printf("\nFibonacci number obtained \n");
    printf("---RECURSIVELY: %d\n", recursiveFibonacciNumber(number));
    printf("---ITERATIVELY: %d\n", iterativeFibonacciNumber(number));
}