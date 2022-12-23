#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef enum
{
    OK = 0,
    PointerIsNull = -1,
    FileNotFound = -2,
    IncorrectInput = -3,
    MemoryAllocationError = -4
} Error;

void printErrors(Error errorCode)
{
    switch (errorCode)
    {
    case PointerIsNull:
        printf("Error with memory!\n");
        break;
    case FileNotFound:
        printf("File not found!\n");
        break;
    case IncorrectInput:
        printf("Incorrect data in input file!\n");
        break;
    case MemoryAllocationError:
        printf("Memory allocation error!\n");
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

Error findAndPrintSaddlePoints(int **matrix, int linesAmount, int columnsAmount)
{
    int *minimumsInLines = calloc(linesAmount, sizeof(int));
    if (minimumsInLines == NULL)
    {
        printErrors(MemoryAllocationError);
        return MemoryAllocationError;
    }
    findMinimumsInLines(matrix, linesAmount, columnsAmount, minimumsInLines);

    int *maximumsInColumns = calloc(columnsAmount, sizeof(int));
    if (maximumsInColumns == NULL)
    {
        printErrors(MemoryAllocationError);
        return MemoryAllocationError;
    }
    findMaximumsInColumns(matrix, linesAmount, columnsAmount, maximumsInColumns);

    bool areThereSaddlePoints = false;
    printf("Saddle points: ");
    for (int i = 0; i < linesAmount; i++)
    {
        for (int j = 0; j < columnsAmount; j++)
        {
            if (minimumsInLines[i] == maximumsInColumns[j])
            {
                printf("%d %d\n", i, j);
                areThereSaddlePoints = true;
            }
        }
    }

    if (!areThereSaddlePoints)
    {
        printf("there are no saddle points in your matrix :(\n");
    }
    free(maximumsInColumns);
    free(minimumsInLines);
    return OK;
}

int main()
{
    int errorCode = OK;
    FILE *file = fopen("matrix.txt", "r");
    if (file == NULL)
    {
        printErrors(errorCode);
        return FileNotFound;
    }

    int linesAmount = 0;
    int columnsAmount = 0;

    errorCode = fscanf(file, "%d %d", &linesAmount, &columnsAmount);
    if (errorCode != 2)
    {
        printErrors(errorCode);
        fclose(file);
        return IncorrectInput;
    }

    int **matrix = calloc(linesAmount, sizeof(int *));
    if (matrix == NULL)
    {
        printErrors(MemoryAllocationError);
        fclose(file);
        return MemoryAllocationError;
    }
    for (int i = 0; i < linesAmount; ++i)
    {
        matrix[i] = calloc(columnsAmount, sizeof(int));
        if (matrix[i] == NULL)
        {
            printErrors(MemoryAllocationError);
            fclose(file);
            return MemoryAllocationError;
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
                return errorCode;
                fclose(file);
            }
        }
    }

    int tmp = 0;
    errorCode = fscanf(file, "%d", &tmp);
    if (errorCode != EOF)
    {
        printErrors(IncorrectInput);
        fclose(file);
        return IncorrectInput;
    }
    fclose(file);

    printMatrix(matrix, linesAmount, columnsAmount);

    errorCode = findAndPrintSaddlePoints(matrix, linesAmount, columnsAmount);
    if (errorCode != OK)
    {
        printErrors(errorCode);
        return errorCode;
    }

    for (int i = 0; i < linesAmount; ++i)
    {
        free(matrix[i]);
    }
    free(matrix);
    return OK;
}