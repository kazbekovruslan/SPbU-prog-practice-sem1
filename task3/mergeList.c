#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxLength 256

typedef int Error;

typedef struct List
{
    char name[maxLength];
    char phone[maxLength];
    struct List *next;
} List;

Error addRecord(List **head, char *name, char *phone)
{
    List *record = calloc(1, sizeof(List));
    if (record == NULL)
    {
        return -1;
    }
    strcpy(record->name, name);
    strcpy(record->phone, phone);
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
        printf("%s %s\n", head->name, head->phone);
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
    return strcmp(left->phone, right->phone);
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
