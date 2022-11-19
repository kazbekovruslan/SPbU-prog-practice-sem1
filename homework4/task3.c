#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define bookSize 100
#define nameSize 100
#define phoneSize 20


void outputBook(FILE *file)
{
    printf("PHONEBOOK:\n");
    int counter = 1;
    while (!feof(file))
    {
        char buffer[nameSize + phoneSize] = "";
        fgets(buffer, nameSize + phoneSize, file);
        printf("%d. %s", counter++, buffer);
    }
    printf("\n\n");
}

void searchPhoneByName(FILE *file, char *nameForSearch)
{
    while (!feof(file))
    {
        char buffer[nameSize + phoneSize] = "";
        fgets(buffer, nameSize + phoneSize, file);

        char name[nameSize] = "";
        char phone[phoneSize] = "";
        int plusIndex = 0;

        for (int i = 0; i < nameSize; ++i)
        {
            name[i] = buffer[i];
            if (buffer[i + 2] == '+')
            {
                plusIndex = i + 2;
                break;
            }
        }

        if (strcmp(name, nameForSearch) == 0)
        {
            for (int i = plusIndex; i < nameSize + phoneSize; ++i)
            {
                if (buffer[i] != '\n')
                {
                    phone[i-plusIndex] = buffer[i];
                }
                else
                {
                    break;
                }
            }
            printf("Number of %s: %s", nameForSearch, phone);
            break;
        }
    }
}


void searchNameByPhone(FILE *file, char *phoneForSearch)
{
    while (!feof(file))
    {
        char buffer[nameSize + phoneSize] = "";
        fgets(buffer, nameSize + phoneSize, file);

        char name[nameSize] = "";
        char phone[phoneSize] = "";
        int plusIndex = 0;

        for (int i = 0; i < nameSize; ++i)
        {
            name[i] = buffer[i];
            if (buffer[i + 2] == '+')
            {
                plusIndex = i + 2;
                break;
            }
        }

        for (int i = plusIndex; i < nameSize + phoneSize; ++i)
        {
            if (buffer[i] != '\n')
            {
                phone[i-plusIndex] = buffer[i];
            }
            else
            {
                break;
            }
        }

        if (strcmp(phone, phoneForSearch) == 0)
        {
            printf("Name for number %s: %s", phoneForSearch, name);
            break;
        }
    }
}


int main()
{

    bool flagIn = true;

    char name[nameSize] = "";
    char phone[phoneSize] = "";

    printf("------------PHONEBOOK------------\n");
    printf("There are 6 functions:\n");
    printf("0 - exit\n");
    printf("1 - add a record (name and phone)\n");
    printf("2 - print all records\n");
    printf("3 - find phone by name\n");
    printf("4 - find name by phone\n");
    printf("5 - save current data in file\n");
    printf("---------------------------------\n");
    while (flagIn)
    {
        int scanResult = 0;
        int numberOfFunction = 0;

        while (!scanResult)
        {
            printf("Enter the number of the function: ");
            scanResult = scanf("%d", &numberOfFunction);
            if (!scanResult)
            {
                printf("Incorrect input. Number is required. Try again!\n");
                scanf("%*[^\n]");
            }
        }

        

        switch (numberOfFunction)
        {
            case 0:
            {
                printf("Goodbye!\n");
                flagIn = false;
                break;
            }
            case 1:
            {
                printf("Enter the name: ");
                getchar();
                gets(name);
                printf("Enter the phone (+xxxxxxxxxxx format): ");
                scanf("%s", &phone);
                printf("Data received!\n\n");
                break;
            }
            case 2: 
            {
                FILE *file = fopen("phonebook.txt", "r");
                if (file == NULL)
                {
                    printf("File not found!");
                    return 1;
                }

                char buffer[nameSize + phoneSize] = "";
                fgets(buffer, nameSize + phoneSize, file);
                if (strlen(buffer) > 0)
                {
                    fseek(file, 0, SEEK_SET); 
                    outputBook(file);
                }
                else
                {
                    printf("Phonebook is empty!\n\n");
                }
                
                break;
            }
            case 3: 
            {
                FILE *file = fopen("phonebook.txt", "r");
                if (file == NULL)
                {
                    printf("File not found!");
                    return 1;
                }

                char nameForSearch[nameSize] = "";
                printf("Enter the name: ");
                getchar();
                gets(nameForSearch);


                searchPhoneByName(file, nameForSearch);
                
                printf("\n\n");
                break;
            }
            case 4:
            {
                FILE *file = fopen("phonebook.txt", "r");
                if (file == NULL)
                {
                    printf("File not found!");
                    return 1;
                }

                char phoneForSearch[phoneSize] = "";
                printf("Enter the phone: ");
                getchar();
                gets(phoneForSearch);


                searchNameByPhone(file, phoneForSearch);
                
                printf("\n\n");
                break;
            }
            case 5:
            {
                FILE *file = fopen("phonebook.txt", "a+");
                if (file == NULL)
                {
                    printf("File not found!");
                    return 1;
                }
                fprintf(file, "%s %s\n", name, phone);
                printf("Your data is recorded:\n%s %s\n", name, phone);
                fclose(file);
                break;
            }
            default: 
            {
                printf("Incorrect number. Try numbers 0 - 5\n");
                break;
            }
        }
    }
    return 0;
}