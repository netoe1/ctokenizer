/*
    Copyright 2025 Ely Torres Neto

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Node
{
    char *token;
    struct Node *next;
} TokenNode;

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
