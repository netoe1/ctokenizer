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
    if (!fullString || !separator || !storage)
    {
        fprintf(stderr, "tokenize-err: Invalid parameters on tokenize() call!\n");
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
        sanitizeToken(token);  // <<< sanitiza antes de armazenar
        if (strlen(token) > 0) // evita armazenar tokens vazios
            addToken(storage, token);
        token = strtok(NULL, separator);
    }

    free(copy);
}
