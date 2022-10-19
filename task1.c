#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool isPalindrome(char *string, int stringLength)
{
    if (string == "")
    {
        return true;
    }
    for (int i = 0; i < stringLength / 2; ++i)
    {
        if (string[i] != string[stringLength - i - 1])
        {
            return false;
        }
    }
    return true;
}


bool test1()
{
    char string[6] = "abccba";
    if (isPalindrome(string, 6)) return true;
    return false;
}

bool test2()
{
    char string[6] = "abcbca";
    if (!isPalindrome(string, 6)) return true;
    return false;
}

bool test3()
{
    char *string = "";
    if (isPalindrome(string, 0)) return true;
    return false;
}


int main()
{
    if (test1() && test2() && test3())
    {
        printf("TEST PASSED!\n\n");
    }
    else
    {
        printf("TEST FAILED!\n\n");
    }

    int stringLength = 0;
    printf("Enter the length of the string: ");
    scanf("%d", &stringLength);

    char *string = (char*) calloc(stringLength + 1, sizeof(char));
    if (string == NULL)
    {
        printf("Memory error!");
        return -1;
    }

    printf("Enter the string: ");
    scanf("%s", string);
    printf("%s\n", string);

    if (isPalindrome(string, stringLength))
    {
        printf("Your string is palindrome!\n");
        return 0;
    }
    printf("Your string is NOT palindrome!\n");

    free(string);
    return 0;
}