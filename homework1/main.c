#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define sumsAmount 28
#define arraySize 1000
#define amountOfDigits 10


float task1(float x) {
    float xSquare = x * x;
    float result = xSquare * (xSquare + x + 1) + x + 1;

    return result;
}


int task2(int divisible, int divider) {
    int counter = 0;
    if (divisible < 0 && divisible % divider != 0) {
        ++counter;
    }

    int signedDivisible = divisible;
    int signedDivider = divider;
    divisible = abs(divisible);
    divider = abs(divider);

    while (divisible >= divider) {
        divisible -= divider;
        ++counter;
    }

    if (signedDivisible < 0 ^ signedDivider < 0) {
        counter = -counter;
    }
    return counter;
}


int reverseArray(int* array, int end) {
    for (int i = 0; i < end / 2; ++i) {
        int a = array[i];
        array[i] = array[end - i - 1];
        array[end - i - 1] = a;
    }
}


int task4(void) {
    int sumsCounts[sumsAmount] = { 0 };

    for (int fstDigit = 0; fstDigit < amountOfDigits; ++fstDigit) {
        for (int sndDigit = 0; sndDigit < amountOfDigits; ++sndDigit) {
            for (int thrdDigit = 0; thrdDigit < amountOfDigits; ++thrdDigit) {
                ++sumsCounts[fstDigit + sndDigit + thrdDigit];
            }
        }
    }

    int luckyTicketsAmount = 0;
    for (int i = 0; i < sumsAmount; ++i) {
        luckyTicketsAmount += sumsCounts[i] * sumsCounts[i];
    }

    return luckyTicketsAmount;
}


bool task5(char string[]) {
    int countOpenedBrackets = 0;

    int stringLength = strlen(string);


    for (int i = 0; i < stringLength; ++i) {
        if (string[i] == '(') {
            ++countOpenedBrackets;
        }
        else {
            if (string[i] == ')') {
                --countOpenedBrackets;
            }
            if (countOpenedBrackets < 0) {
                break;
            }
        }
    }

    return (countOpenedBrackets == 0);
}

int task6(char string[], char substring[]) {
    int countEntry = 0;


    int lengthString = strlen(string);
    int lengthSubString = strlen(substring);


    for (int i = 0; i <= lengthString - lengthSubString; ++i) {
        for (int j = 0; j < lengthSubString; ++j) {
            if (string[i + j] != substring[j]) {
                break;
            }

            if (j == lengthSubString - 1) {
                ++countEntry;
            }
        }
    }
    return countEntry;
}

int main() {

    bool exitFlag = true;

    while (exitFlag) {

        int number = 0;
        printf("Enter the task number 1-8 ('0' to exit): ");
        scanf("%d", &number);


        switch (number) {
        case 1: {
            float x = 0;
            float result1 = 0;



            printf("Enter X: ");
            scanf("%f", &x);

            result1 = task1(x);
            printf("Result of x^4 + x^3 + x^2 + x + 1 is %f\n\n", result1);
            break;
        }
        case 2: {

            int divisible = 0;
            int divider = 0;

            printf("Enter divisible and divider: ");
            scanf("%d%d", &divisible, &divider);

            printf("Incomplete quotent in division: %d/%d = %d\n\n", divisible, divider, task2(divisible, divider));


            break;
        }
        case 3: {
            int array[arraySize] = { 0 };
            int firstIndex = 0;
            int secondIndex = 0;
            int arrayLength = 0;


            bool isIncorrectInput = true;
            while (isIncorrectInput) {
                printf("Enter lengths of two parts of the array: ");
                scanf("%d%d", &firstIndex, &secondIndex);
                if (firstIndex < 0 || secondIndex < 0) isIncorrectInput = true;
                else isIncorrectInput = false;
                if (isIncorrectInput) printf("Incorrect input. Both numbers aren't negative. Try again!\n");
            }


            arrayLength = firstIndex + secondIndex;


            printf("Enter the array: ");

            for (int i = 0; i < arrayLength; ++i) {
                scanf("%d", &array[i]);
            }

            reverseArray(array, firstIndex); //переворот первой части
            reverseArray(array, arrayLength); //переворот всего массива
            reverseArray(array, secondIndex); //переворот второй части



            for (int i = 0; i < arrayLength; ++i) {
                printf("%d ", array[i]);
            }
            printf("\n\n");


            break;
        }
        case 4: {
            int luckyTicketsAmount = 0;

            luckyTicketsAmount = task4();
            printf("Amount of lucky tickets with length 6 is %d\n\n", luckyTicketsAmount);
            break;
        }
        case 5: {
            char string[100] = "";

            printf("Enter the sequence: ");
            scanf("%s", string, 100);

            if (task5(string)) {
                printf("Bracket sequence is correct\n\n");
            }
            else {
                printf("Bracket sequence is incorrect\n\n");
            }



            break;
        }
        case 6: {
            char string[100] = "";
            char substring[100] = "";


            printf("Enter the string (<100 symbols): ");
            scanf("%s", string, 100);
            printf("Enter the substring (<100 symbols): ");
            scanf("%s", substring, 100);

            printf("Amount of entries of substring in string is %d\n\n", task6(string, substring));


            break;
        }
        case 7: {
            int number = 0;
            bool arrayPrimeNumbers[arraySize] = { false };



            printf("Enter your number (0 < x < 1000): ");
            scanf("%d", &number);

            if (number < 0) {
                printf("Your number is negative, try again\n\n");
                break;
            }

            if (number > 1000) {
                printf("Your number is too big, try again\n\n");
                break;
            }
            
            if (number < 2) {
                printf("There are no prime numbers below your number\n\n");
                break;
            }
            
            for (int i = 0; i <= number; ++i) {
                arrayPrimeNumbers[i] = true;
            }

            arrayPrimeNumbers[0] = false;
            arrayPrimeNumbers[1] = false;

            for (int i = 2; i <= number; ++i) {
                if (arrayPrimeNumbers[i] == true) {
                    for (int j = i * 2; j <= number; j += i) {
                        arrayPrimeNumbers[j] = false;
                    }
                }
            }

            printf("Prime numbers that are not above your number: ");
            for (int i = 0; i <= number; ++i) {
                if (arrayPrimeNumbers[i] == true) {
                    printf("%d ", i);
                }
            }
            printf("\n\n");
            

            break;
        }
        case 8: {
            int arrayLength = 0;
            int element = 0;
            int counterNonZeroElements = 0;

            printf("Enter the size of array: ");
            scanf("%d", &arrayLength);
            printf("Enter the array: ");
            for (int i = 0; i < arrayLength; ++i) {
                scanf("%d", &element);
                if (element != 0) {
                    ++counterNonZeroElements;
                }
            }

            printf("Amount of non-zero elements in your array is %d\n\n", counterNonZeroElements);

            break;
        }
        case 0: {
            exitFlag = false;
            printf("Bye!");
        }

        }
    }

    return 0;
}