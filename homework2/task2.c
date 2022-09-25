#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


float exponentiation(float number, int degree)
{
    float exponentiatedNumber = 1;

    if (degree == 0) return 1;

    for (int i = 0; i < abs(degree); ++i)
    {
        exponentiatedNumber *= number;
    }

    if (degree < 0)
    {
        exponentiatedNumber = 1 / exponentiatedNumber;
    }

    return exponentiatedNumber;
}


float exponentiationLog(float number, int degree)
{
    float transitNumber = number;
    float exponentiatedNumber = 1;
    bool isDegreeNegative = false;

    if (degree == 0) return 1;

    if (degree < 0) isDegreeNegative = true;

    degree = abs(degree);
    
    
    while (degree != 0)
    {
        if (degree % 2 == 1)
        {
            exponentiatedNumber *= transitNumber;
        }
        transitNumber = transitNumber * transitNumber;
        degree /= 2;
    }

    if (isDegreeNegative) return 1/exponentiatedNumber;
    return exponentiatedNumber;
}


bool test()
{
    for (float number = -10; number < 10; ++number)
    {
        for (int degree = -10; degree < 10; ++degree)
        {
            if (number != 0 && degree != 0)
            {
                if (exponentiation(number,degree) != exponentiationLog(number,degree))
                {   
                    printf("ERROR! TESTS FAILED!\n");
                    printf("Number = %f, degree = %d, first = %f, second = %f\n", number, degree, exponentiation(number,degree), exponentiationLog(number,degree));
                    return false;
                }
            }
        }
    }
    return true;
}




void main(void)
{
    test();


    float number = 0;
    int degree = 0;
    
    int scanResult = 0;
    while (!scanResult)
    {
        printf("Enter the number you want to raise to a power (float): ");
        scanResult = scanf("%f", &number);
        if (!scanResult)
        {
            printf("Incorrect input. Float number is required. Try again!\n");
            scanf_s("%*[^\n]");
        }
    }


    scanResult = 0;
    while (!scanResult)
    {
        printf("Enter the degree (natural number): ");
        scanResult = scanf("%d", &degree);
        if (!scanResult)
        {
            printf("Incorrect input. Natural number is required. Try again!\n");
            scanf_s("%*[^\n]");
        }
    }

    if (degree == 0 && number == 0)
    {
        printf("0/0 is undetermined\n");
        return;
    }


    int typeOfExponentiation = 0;
    scanResult = 0;
    printf("What type of exponentiation do you want to use? ");
    while (!scanResult)
    {
        printf("1 - O(n), 2 - O(log n)\nEnter here: ");
        scanResult = scanf_s("%d", &typeOfExponentiation);
        if (!scanResult)
        {
            printf("Incorrect input. Number is required. Try again!\n");
            scanf_s("%*[^\n]");
        }
    }
    
    printf("Exponentiated number: ");

    if (typeOfExponentiation == 1)
    {
        printf("%f", exponentiation(number, degree));
    }
    else
    {
        printf("%f", exponentiationLog(number, degree));
    }
}