#include <stdio.h>
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
        bit = bit << 1;
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
    int extraUnit = 0;
    int extraSum = 0;
    for (int i = binaryNumberLength - 1; i >= 0; --i)
    {
        extraSum = firstBinaryNumber[i] + secondBinaryNumber[i] + extraUnit;
        sumResult[i] = extraSum & 1;
        extraUnit = extraSum >> 1;
    }
}

void main()
{
    setlocale(LC_ALL, "");

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