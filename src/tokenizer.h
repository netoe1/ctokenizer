/*
 * tokenizer.h
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

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char *token;
    struct Node *next;
};

struct Node *createNode(const char *value);
void addToken(struct Node **head, const char *value);
void removeTokenByContent(struct Node **head, const char *value);
void removeTokenByIndex(struct Node **head, int index);
int getTokenByIndex(struct Node *head, const char *value);
void printTokens(struct Node *head);
void freeList(struct Node *head);
void tokenize(struct Node **storage, const char *fullString, const char *separator);
void sanitizeToken(char *str);

#endif
