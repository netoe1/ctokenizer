#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

struct Node
{
    char *token;
    struct Node *next;
};

struct Node *createNode(const char *value)
{
    struct Node *newNode = malloc(sizeof(struct Node));
    if (!newNode)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->token = strdup(value);
    newNode->next = NULL;
    return newNode;
}

void addToken(struct Node **head, const char *value)
{
    struct Node *newNode = createNode(value);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    struct Node *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

void removeTokenByContent(struct Node **head, const char *value)
{
    struct Node *current = *head;
    struct Node *previous = NULL;

    while (current != NULL)
    {
        if (strcmp(current->token, value) == 0)
        {
            if (previous == NULL)
            {
                *head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            free(current->token);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void removeTokenByIndex(struct Node **head, int index)
{
    if (index < 0 || *head == NULL)
        return;

    struct Node *current = *head;

    if (index == 0)
    {
        *head = current->next;
        free(current->token);
        free(current);
        return;
    }

    struct Node *previous = NULL;
    for (int i = 0; current != NULL && i < index; i++)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
        return;

    previous->next = current->next;
    free(current->token);
    free(current);
}

int getTokenByIndex(struct Node *head, const char *value)
{
    int index = 0;
    while (head != NULL)
    {
        if (strcmp(head->token, value) == 0)
        {
            return index;
        }
        head = head->next;
        index++;
    }
    return -1;
}

void printTokens(struct Node *head)
{
    if (!head)
    {
        printf("Lista vazia.\n");
        return;
    }
    while (head != NULL)
    {
        printf("%s -> ", head->token);
        head = head->next;
    }
    printf("NULL\n");
}

void freeList(struct Node *head)
{
    struct Node *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp->token);
        free(temp);
    }
}

void tokenize(struct Node **storage, const char *fullString, const char *separator)
{
    if (!fullString || !separator || !storage)
    {
        fprintf(stderr, "tokenize-err: Invalid parameters on tokenize() call!");
        return;
    }

    char *copy = strdup(fullString);
    if (!copy)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    char *token = strtok(copy, separator);
    while (token != NULL)
    {
        addToken(storage, token);
        token = strtok(NULL, separator); // <--- CORRETO AQUI
    }

    free(copy);
}
