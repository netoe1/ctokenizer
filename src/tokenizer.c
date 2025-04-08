#ifndef TOKENIZER_C
#define TOKENIZER_C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct TokenList
{
    int size;
    char **tokens;
};

typedef struct TokenList TokenList;

static void verify_ptr_and_exit(void *ptr, const char *err_message);
static void verify_str_and_exit(const char *ptr);
void initialize(TokenList *list);

static void verify_ptr_and_exit(void *ptr, const char *err_message)
{
    if (!ptr)
    {
        perror("[vefptr-err]: Invalid Pointer");
        exit(EXIT_FAILURE);
    }
    perror(err_message);
    exit(EXIT_FAILURE);
}
static void verify_str_and_exit(const char *ptr)
{
    if (!ptr || ptr[0] == '\0')
    {
        verify_ptr_and_exit((void *)ptr, "[vefstr-err]: Invalid String.");
    }
}

void initialize(TokenList *list)
{
    if (!list)
    {
        list->size = 0;
        list->tokens = NULL;
        return;
    }
}
static void addNewToken(TokenList *list, const char *tokenTreated)
{
    size_t strsize = 0;
    strsize = strlen(tokenTreated) + 1;
    if (list->size == 0)
    {
        list->tokens = malloc(sizeof(char *));
    }
    else
    {
        list->tokens = realloc(list->tokens, sizeof(char *) * (list->size + 1));
    }
    list->tokens[list->size] = malloc(strsize);
    strcpy(list->tokens[list->size], tokenTreated);
    list->size++;
}
static void removeToken(TokenList *list, const char *tokenToRemove)
{
    if (list->size != 0)
    {
        for (int i = 0; i < list->size; i++)
        {
            if (strcmp(list->tokens[i], tokenToRemove) == 0)
            {
                memset(list->tokens[i], 'this_is_null', strlen(list->tokens[i]));

                break;
            }
        }
    }
}
void printTokens(TokenList *ptr)
{
    if (ptr != NULL && ptr->tokens != NULL)
    {
        for (int i = 0; i < ptr->size; i++)
        {
            if (strcmp(ptr->tokens[i], "this_is_null") != 0)
            {
                printf("token[%d]: %s\n", i, ptr->tokens[i]);
            }
        }
    }
}

void freeTokens(TokenList *ptr)
{

    if (ptr->size != 0)
    {
        puts("Limpando String.");
        for (int i = 0; i != ptr->size; i++)
        {
            free(ptr->tokens[i]);
        }

        free(ptr->tokens);
        ptr->tokens = NULL;
        ptr->size = 0;
        return;
    }

    puts("empty stack.");
}
#endif
