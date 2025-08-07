/*
 * tokenizer.c
 * Copyright (C) 2025 Ely Neto
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU GPL along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "tokenizer.h"

// static int containTerminator(const char *str, const char *separator)
// {
//     if (!str || !separator)
//     {
//         fprintf(stderr, "containTerminator-err: NULL string or separator provided!\n");
//         return -1;
//     }

//     for (int i = 0; str[i] != '\0'; i++)
//     {
//         if (strchr(separator, str[i]) != NULL)
//         {
//             return 1;
//         }
//     }
//     return 0;
// }
struct Node *createNode(const char *value)
{

    if (!value)
    {
        fprintf(stderr, "createNode-err: NULL value provided to createNode()!\n");
        exit(-1);
    }
    struct Node *newNode = malloc(sizeof(struct Node));
    if (!newNode)
    {
        printf("Memory allocation failed!\n");
        exit(-1);
    }
    // set all bytes to 0, avoiding garbage values
    memset(newNode, 0, sizeof(struct Node));
    newNode->next = NULL;
    newNode->token = strdup(value);

    if (!newNode->token)
    {
        fprintf(stderr, "createNode-err: cannot duplicate token!\n");
        free(newNode);
        exit(-1);
    }

    return newNode;
}

void addToken(struct Node **head, const char *value)
{
    if (!head || !value)
    {
        fprintf(stderr, "addToken-err: Invalid parameters on addToken() call!\n");
        return;
    }
    struct Node *newNode = createNode(value);

    // Garante que *head está inicializado
    if (*head != NULL && ((uintptr_t)*head < 4096))
    {
        fprintf(stderr, "addToken-err: Head pointer is invalid!\n");
        *head = NULL;
    }

    if (!newNode)
    {
        fprintf(stderr, "addToken-err: Memory allocation failed in addToken()!\n");
        return;
    }

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
    if (!head || !value)
    {
        fprintf(stderr, "removeTokenByContent-err: Invalid parameters on removeTokenByContent() call!\n");
        return;
    }

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

    if (!head)
    {
        fprintf(stderr, "removeTokenByIndex-err: NULL head pointer provided to removeTokenByIndex()!\n");
        return;
    }

    if (!index && index != 0)
    {
        fprintf(stderr, "removeTokenByIndex-err: Invalid index provided to removeTokenByIndex()!\n");
        return;
    }

    if (index < 0)
    {
        fprintf(stderr, "removeTokenByIndex-err: Negative index provided to removeTokenByIndex()!\n");
        return;
    }

    if (*head == NULL)
    {
        fprintf(stderr, "removeTokenByIndex-err: *Head is null!\n");
        return;
    }

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
    if (!head)
    {
        fprintf(stderr, "getTokenByIndex-err: NULL head pointer provided to getTokenByIndex()!\n");
        return -1;
    }

    if (!value)
    {
        fprintf(stderr, "getTokenByIndex-err: NULL value pointer provided to getTokenByIndex()!\n");
        return -1;
    }

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
        fprintf(stderr, "printTokens-err: The list is empty!\n");
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

void sanitizeToken(char *str)
{
    // Remove newline
    str[strcspn(str, "\n")] = '\0';

    // Remove leading spaces
    char *start = str;
    while (*start == ' ' || *start == '\t')
        start++;

    // Remove trailing spaces
    char *end = start + strlen(start) - 1;
    while (end > start && (*end == ' ' || *end == '\t'))
    {
        *end = '\0';
        end--;
    }

    // Move conteúdo se houver espaço no início
    if (start != str)
        memmove(str, start, strlen(start) + 1);
}

void tokenize(struct Node **storage, const char *fullString, const char *separator)
{

    if (!fullString || !separator || !storage || !*storage)
    {
        fprintf(stderr, "tokenize-err: Invalid parameters on tokenize() call!\n");
        return;
    }

    if (*storage == NULL)
        *storage = NULL;

    char *copy = strdup(fullString);
    if (!copy)
    {
        fprintf(stderr, "tokenize-err: Memory allocation failed in tokenize()!\n");
        return;
    }

    char *token = strtok(copy, separator);
    if (token == NULL)
    {
        fprintf(stderr, "tokenize-err: No separatorns found in the provided string!\n");
        free(copy);
        freeList(*storage);
        return;
    }
    while (token != NULL)
    {
        sanitizeToken(token);
        if (strlen(token) > 0)
            addToken(storage, token);
        token = strtok(NULL, separator);
    }

    free(copy);
}
