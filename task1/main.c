#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define maxLengthForBinary 256

int divisionWithRoundingUp(int first, int second)
{
    int result = first / second;
    if (first == result * second)
    {
        return result;
    }
    return result + 1;
}

char binaryTriadToOctalDigit(char *binaryTriad)
{
    char octalDigit = 0;
    int power = 1;
    for (int i = 2; i >= 0; --i)
    {
        octalDigit += (binaryTriad[i] - '0') * power;
        power <<= 1;
    }
    return octalDigit;
}

void binaryToOctal(char *binaryNumber, char *octalNumber)
{
    int startIndex = 0; // также количество нулей
    int binaryNumberLength = strlen(binaryNumber);
    for (int i = 0; i < binaryNumberLength; ++i)
    {
        if (binaryNumber[i] == '1')
        {
            break;
        }
        ++startIndex;
    }

    char buffer[3] = {0, 0, 0};
    int counterForTriad = 0;
    int iteratorForBuffer = 2;
    int iteratorForOctal = divisionWithRoundingUp(strlen(binaryNumber) - startIndex, 3) - 1;
    for (int i = binaryNumberLength - 1; i >= startIndex; --i)
    {
        buffer[iteratorForBuffer--] = binaryNumber[i];
        ++counterForTriad;
        if (counterForTriad == 3)
        {
            counterForTriad = 0;
            iteratorForBuffer = 2;
            octalNumber[iteratorForOctal--] = binaryTriadToOctalDigit(buffer) + '0';
        }
        if (counterForTriad != 0 && i == startIndex) // в начале нет полной триады
        {
            for (int j = 0; j < 3 - counterForTriad; ++j)
            {
                buffer[j] = '0';
            }
            octalNumber[iteratorForOctal--] = binaryTriadToOctalDigit(buffer) + '0';
        }
    }
}

int main()
{
    char binaryNumber[maxLengthForBinary] = {0};
    printf("Enter the binary number (length <= 256): ");
    scanf("%s", binaryNumber);
    int iterator = 0;
    while (binaryNumber[iterator] != '\0')
    {
        if (!(binaryNumber[iterator] == '0' || binaryNumber[iterator] == '1'))
        {
            printf("Incorrect binary number! There are not only '0' and '1'!\n");
            return -2;
        }
        ++iterator;
    }
    char *octalNumber = calloc(divisionWithRoundingUp(strlen(binaryNumber), 3) + 1, sizeof(char));
    if (octalNumber == NULL)
    {
        printf("Memory error!\n");
        return -1;
    }
    binaryToOctal(binaryNumber, octalNumber);
    printf("Your octal number: %s", octalNumber);
    return 0;
}