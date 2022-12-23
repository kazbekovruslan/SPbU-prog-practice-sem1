#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef enum
{
    OK = 0,
    PointerIsNull = -1,
    FileNotFound = -2,
    IncorrectInput = -3
} Error;

void printErrors(Error errorCode)
{
    switch (errorCode)
    {
    case OK:
        break;
    case PointerIsNull:
        printf("Error with memory!\n");
        break;
    case FileNotFound:
        printf("File not found!\n");
        break;
    case IncorrectInput:
        printf("Incorrect data in input file!\n");
        break;
    }
}

void printMatrix(int **matrix, int linesAmount, int columnsAmount)
{
    printf("Your matrix:\n");
    for (int i = 0; i < linesAmount; ++i)
    {
        for (int j = 0; j < columnsAmount; ++j)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void findMinimumsInLines(int **matrix, int linesAmount, int columnsAmount, int *minimumsInLines)
{
    for (int i = 0; i < linesAmount; ++i)
    {
        minimumsInLines[i] = INT_MAX;
        for (int j = 0; j < columnsAmount; ++j)
        {
            if (matrix[i][j] < minimumsInLines[i])
            {
                minimumsInLines[i] = matrix[i][j];
            }
        }
    }
}

void findMaximumsInColumns(int **matrix, int linesAmount, int columnsAmount, int *maximumsInColumns)
{
    for (int j = 0; j < columnsAmount; ++j)
    {
        maximumsInColumns[j] = INT_MIN;
        for (int i = 0; i < linesAmount; ++i)
        {
            if (matrix[i][j] > maximumsInColumns[j])
            {
                maximumsInColumns[j] = matrix[i][j];
            }
        }
    }
}

void findAndPrintSaddlePoints(int **matrix, int linesAmount, int columnsAmount, int *maximumsInColumns, int *minimumsInLines)
{
    bool saddlePointsFlag = false;
    printf("Saddle points: ");
    for (int i = 0; i < linesAmount; i++)
    {
        for (int j = 0; j < columnsAmount; j++)
        {
            if (minimumsInLines[i] == maximumsInColumns[j])
            {
                printf("%d %d\n", i, j);
                saddlePointsFlag = true;
            }
        }
    }

    if (!saddlePointsFlag)
    {
        printf("there are no saddle points in your matrix :(\n");
    }
}

int main()
{
    int errorCode = OK;
    FILE *file = fopen("matrix.txt", "r");
    if (file == NULL)
    {
        printf("File not found!\n");
        return FileNotFound;
    }

    int linesAmount = 0;
    int columnsAmount = 0;

    errorCode = fscanf(file, "%d %d", &linesAmount, &columnsAmount);
    if (errorCode != 2)
    {
        printErrors(errorCode);
        return IncorrectInput;
    }

    int **matrix = calloc(linesAmount, sizeof(int *));
    if (matrix == NULL)
    {
        printf("Memory allocation error!\n");
        return -100;
    }
    for (int i = 0; i < linesAmount; ++i)
    {
        matrix[i] = calloc(columnsAmount, sizeof(int));
        if (matrix[i] == NULL)
        {
            printf("Memory allocation error!\n");
            return -100;
        }
    }

    for (int i = 0; i < linesAmount; ++i)
    {
        for (int j = 0; j < columnsAmount; ++j)
        {
            errorCode = fscanf(file, "%d", &matrix[i][j]);
            if (errorCode != 1)
            {
                printErrors(errorCode);
            }
        }
    }

    int tmp = 0;
    errorCode = fscanf(file, "%d", &tmp);
    if (errorCode != EOF)
    {
        printErrors(IncorrectInput);
        return IncorrectInput;
    }

    printMatrix(matrix, linesAmount, columnsAmount);

    int *minimumsInLines = calloc(linesAmount, sizeof(int));
    if (minimumsInLines == NULL)
    {
        printf("Memory allocation error!\n");
        return -100;
    }
    findMinimumsInLines(matrix, linesAmount, columnsAmount, minimumsInLines);

    int *maximumsInColumns = calloc(columnsAmount, sizeof(int));
    if (maximumsInColumns == NULL)
    {
        printf("Memory allocation error!\n");
        return -100;
    }
    findMaximumsInColumns(matrix, linesAmount, columnsAmount, maximumsInColumns);

    findAndPrintSaddlePoints(matrix, linesAmount, columnsAmount, maximumsInColumns, minimumsInLines);

    for (int i = 0; i < linesAmount; ++i)
    {
        free(matrix[i]);
    }
    free(matrix);
    return OK;
}