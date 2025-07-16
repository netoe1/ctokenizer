#ifndef TOKENIZE_H
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

#endif
