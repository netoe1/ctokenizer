#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

struct Node
{
    char *token;
    struct Node *next;
};

// Helper: Create a new node
struct Node *createNode(const char *value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (!newNode)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->token = strdup(value);
    newNode->next = NULL;
    return newNode;
}

// Add token at the end
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

// Remove first node with matching content
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
                *head = current->next; // removing the head
            }
            else
            {
                previous->next = current->next; // re-link
            }
            free(current->token);
            free(current);
            return; // remove only first match
        }
        previous = current;
        current = current->next;
    }
}

// Remove node by index
void removeTokenByIndex(struct Node **head, int index)
{
    if (index < 0 || *head == NULL)
        return;

    struct Node *current = *head;
    struct Node *previous = NULL;

    for (int i = 0; current != NULL && i < index; i++)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
        return; // index out of bounds

    if (previous == NULL)
    {
        *head = current->next; // removing the head
    }
    else
    {
        previous->next = current->next; // re-link
    }
    free(current->token);
    free(current);
}

// Get index of first matching token
int getTokenIndex(struct Node *head, const char *value)
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

// Print the entire list
void printList(struct Node *head)
{
    while (head != NULL)
    {
        printf("%s -> ", head->token);
        head = head->next;
    }
    printf("NULL\n");
}

// Free memory
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

void tokenize(struct Node **storage, const char *fullString)
{

    // Create a copy of the string because strtok modifies it
    char *copy = strdup(fullString);
    if (!copy)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    char *token = strtok(copy, " \t\n"); // split by space/tab/newline

    while (token != NULL)
    {
        addToken(storage, token);
        token = strtok(NULL, " \t\n");
    }

    free(copy); // Clean up the copied string
}