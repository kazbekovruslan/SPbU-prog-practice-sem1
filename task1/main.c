#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isDigit(char symbol)
{
    return symbol >= 48 && symbol <= 57;
}

bool isDate(char *date)
{
    char day[2] = {0};
    char month[2] = {0};
    char year[4] = {0};
    for (int i = 0; i < 2; ++i)
    {
        day[i] = date[i];
    }
    for (int i = 3; i < 5; ++i)
    {
        month[i - 3] = date[i];
    }
    for (int i = 6; i < 10; ++i)
    {
        year[i - 6] = date[i];
    }
    return strcmp(day, "00") > 0 && strcmp(day, "31") < 0 && strcmp(month, "00") > 0 &&
           strcmp(month, "13") < 0 && strcmp(year, "0000") > 0 && date[2] == '.' && date[5] == '.';
}

int compareDates(char *date, char *maxDate)
{
    char day1[2] = {0};
    char month1[2] = {0};
    char year1[4] = {0};
    for (int i = 0; i < 2; ++i)
    {
        day1[i] = date[i];
    }
    for (int i = 3; i < 5; ++i)
    {
        month1[i - 3] = date[i];
    }
    for (int i = 6; i < 10; ++i)
    {
        year1[i - 6] = date[i];
    }

    char day2[2] = {0};
    char month2[2] = {0};
    char year2[4] = {0};
    for (int i = 0; i < 2; ++i)
    {
        day2[i] = maxDate[i];
    }
    for (int i = 3; i < 5; ++i)
    {
        month2[i - 3] = maxDate[i];
    }
    for (int i = 6; i < 10; ++i)
    {
        year2[i - 6] = maxDate[i];
    }

    if (strcmp(year1, year2) != 0)
    {
        return strcmp(year1, year2);
    }
    else if (strcmp(month1, month2) != 0)
    {
        return strcmp(month1, month2);
    }
    else
    {
        return strcmp(day1, day2);
    }
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("File not found!\n");
        return -2;
    }

    char maxDate[10] = "01.01.0001";
    char date[10] = {0};
    char symbol = 0;
    while (!feof(file))
    {
        symbol = getc(file);
        if (isDigit(symbol))
        {
            for (int i = 0; i < 10; ++i)
            {
                date[i] = symbol;
                symbol = getc(file);
            }
            if (isDate(date))
            {
                if (compareDates(date, maxDate) > 0)
                {
                    strcpy(maxDate, "0000000000");
                    strcpy(maxDate, date);
                }
            }
        }
    }
    printf("%s", maxDate);
    return 0;
}