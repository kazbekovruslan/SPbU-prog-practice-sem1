#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#define binaryNumberLength 32

void printArray(unsigned char *array, int arrayLength)
{
    for (int i = 0; i < arrayLength; ++i)
    {
        printf("%d", array[i]);
    }
    printf("\n");
}

void decimalToBinaryConvert(unsigned char *binaryNumber, int number)
{
    int bit = 1;
    for (int i = binaryNumberLength - 1; i >= 0; --i)
    {
        binaryNumber[i] = (number & bit) ? 1 : 0;
        bit <<= 1;
    }
}

int binaryToDecimalConvert(unsigned char *binaryNumber)
{
    int decimalNumber = 0;
    int power = 1;
    for (int i = binaryNumberLength - 1; i >= 0; --i)
    {
        decimalNumber += binaryNumber[i] * power;
        power *= 2;
    }
    return decimalNumber;
}

void binarySum(unsigned char *sumResult, unsigned char *firstBinaryNumber, unsigned char *secondBinaryNumber)
{
    int transferBit = 0;
    int extraSum = 0;
    for (int i = binaryNumberLength - 1; i >= 0; --i)
    {
        extraSum = firstBinaryNumber[i] + secondBinaryNumber[i] + transferBit;
        sumResult[i] = extraSum & 1;
        transferBit = extraSum >> 1;
    }
}

bool test()
{
    int firstNumbers[5] = {1, 1000, 54, 2147483647, 2147483647};
    int secondNumbers[5] = {-1, 3, -53, -2147483647, 2147483647};
    unsigned char firstBinaryNumber[binaryNumberLength] = {0};
    unsigned char secondBinaryNumber[binaryNumberLength] = {0};
    int firstNumber = 0;
    int secondNumber = 0;
    unsigned char binarySumResult[binaryNumberLength] = {0};
    for (int i = 0; i < 5; ++i)
    {
        decimalToBinaryConvert(firstBinaryNumber, firstNumbers[i]);
        decimalToBinaryConvert(secondBinaryNumber, secondNumbers[i]);
        binarySum(binarySumResult, firstBinaryNumber, secondBinaryNumber);
        if (binaryToDecimalConvert(binarySumResult) != firstNumbers[i] + secondNumbers[i])
        {
            return false;
        }
    }
    return true;
}

void main()
{
    setlocale(LC_ALL, "");
    if (!test())
    {
        printf("Тест провален!\n");
        return;
    }

    int firstNumber = 0;
    int secondNumber = 0;
    unsigned char firstBinaryNumber[binaryNumberLength] = {0};
    unsigned char secondBinaryNumber[binaryNumberLength] = {0};

    int scanResult = 0;
    while (scanResult < 2)
    {
        printf("Введите два числа: ");
        scanResult = scanf("%d%d", &firstNumber, &secondNumber);
        if (scanResult < 2)
        {
            printf("Неправильный ввод. Нужно ввести числа. Попробуйте еще раз!\n");
            scanf("%*[^\n]");
        }
    }

    decimalToBinaryConvert(firstBinaryNumber, firstNumber);
    printf("Двочиное представление первого числа: ");
    printArray(firstBinaryNumber, binaryNumberLength);

    decimalToBinaryConvert(secondBinaryNumber, secondNumber);
    printf("Двоичное представление второго числа: ");
    printArray(secondBinaryNumber, binaryNumberLength);

    printf("                                      --------------------------------\n");

    unsigned char binarySumResult[binaryNumberLength] = {0};

    binarySum(binarySumResult, firstBinaryNumber, secondBinaryNumber);
    printf("Двоичная сумма ваших чисел:           ");
    printArray(binarySumResult, binaryNumberLength);

    printf("Десятичная сумма ваших чисел: %d", binaryToDecimalConvert(binarySumResult));
}