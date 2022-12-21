#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define maxLength 256

typedef int Error;

typedef struct List
{
    char name[maxLength];
    int amount;
    bool mark;
    struct List *next;
} List;

Error addRecord(List **head, char *name, int amount)
{
    List *record = calloc(1, sizeof(List));
    if (record == NULL)
    {
        return -1;
    }
    strcpy(record->name, name);
    record->amount = amount;
    record->next = *head;
    *head = record;
    return 0;
}

void freeList(List **head)
{
    List *tmp = NULL;
    if (head == NULL)
    {
        return;
    }
    while (*head != NULL)
    {
        tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
}

void printList(List *head)
{
    printf("---LIST---\n");
    while (head != NULL)
    {
        printf("%s %d\n", head->name, head->amount);
        head = head->next;
    }
    printf("---END OF LIST---\n\n");
}

int compare(List *left, List *right, int typeOfCompare)
{
    if (typeOfCompare == 0)
    {
        return strcmp(left->name, right->name);
    }
    if (left->amount > right->amount)
    {
        return -1;
    }
    else if (left->amount < right->amount)
    {
        return 1;
    }
    return 0;
}

void split(List *sourceList, List **leftList, List **rightList)
{
    List *fast = NULL;
    List *slow = NULL;

    if (sourceList == NULL || sourceList->next == NULL)
    {
        (*leftList) = sourceList;
        (*rightList) = NULL;
        return;
    }

    slow = sourceList;
    fast = sourceList->next;

    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            fast = fast->next;
            slow = slow->next;
        }
    }

    (*leftList) = sourceList;
    (*rightList) = slow->next;
    slow->next = NULL;
}

void merge(List *leftList, List *rightList, List **resultList, int typeOfCompare)
{
    *resultList = NULL;
    if (leftList == NULL)
    {
        *resultList = rightList;
        return;
    }
    if (rightList == NULL)
    {
        *resultList = leftList;
        return;
    }

    if (compare(leftList, rightList, typeOfCompare) < 0)
    {
        (*resultList) = leftList;
        leftList = leftList->next;
    }
    else
    {
        (*resultList) = rightList;
        rightList = rightList->next;
    }
    List *head = *resultList;

    while (leftList != NULL && rightList != NULL)
    {
        if (compare(leftList, rightList, typeOfCompare) < 0)
        {
            (*resultList)->next = leftList;
            leftList = leftList->next;
        }
        else
        {
            (*resultList)->next = rightList;
            rightList = rightList->next;
        }
        *resultList = (*resultList)->next;
    }

    if (rightList == NULL)
    {
        (*resultList)->next = leftList;
    }
    if (leftList == NULL)
    {
        (*resultList)->next = rightList;
    }

    *resultList = head;
}

void mergeSort(List **head, int typeOfCompare)
{
    List *leftList = NULL;
    List *rightList = NULL;
    if ((*head == NULL) || ((*head)->next == NULL))
    {
        return;
    }
    split(*head, &leftList, &rightList);
    mergeSort(&leftList, typeOfCompare);
    mergeSort(&rightList, typeOfCompare);
    merge(leftList, rightList, head, typeOfCompare);
}

void printFirstPart(List **head, int firstIndex)
{
    if (firstIndex == 0)
    {
        return;
    }
    mergeSort(head, 1);
    int counter = 0;
    printf("Goods with 50%% discount:\n");
    while (*head != NULL && counter < firstIndex)
    {
        printf("%s %d\n", (*head)->name, (*head)->amount);
        (*head)->mark = true;
        ++counter;
        *head = (*head)->next;
    }
    if (counter == 0)
    {
        printf("no such goods :(\n");
    }
}

void printSecondPart(List **head, int secondIndex)
{
    if (secondIndex == 0)
    {
        return;
    }
    mergeSort(head, 0);
    int counter = 0;
    printf("Goods with 25%% discount:\n");
    while (*head != NULL && counter < secondIndex)
    {
        if ((*head)->mark == false)
        {
            printf("%s %d\n", (*head)->name, (*head)->amount);
            (*head)->mark = true;
            ++counter;
        }
        *head = (*head)->next;
    }
    if (counter == 0)
    {
        printf("no such goods :(\n");
    }
}

void printRemainingPart(List **head)
{
    int counter = 0;
    printf("Remaining goods:\n");
    while (*head != NULL)
    {
        if ((*head)->mark == false)
        {
            printf("%s %d\n", (*head)->name, (*head)->amount);
            (*head)->mark = true;
            ++counter;
        }
        *head = (*head)->next;
    }
    if (counter == 0)
    {
        printf("no such goods :(\n");
    }
}