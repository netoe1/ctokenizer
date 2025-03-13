#ifndef TOKENIZER_C
#define TOKENIZER_C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Tokens
{
    int size;
    char **vector;
};

typedef struct Tokens Tokens;

static void verify_ptr_and_exit(void *ptr, const char *err_message);
static void verify_str_and_exit(char *ptr);

void init_tokens(Tokens *ptr);
void free_vectors(Tokens *ptr);
void tokenize(Tokens *ptr, char *prhase, const char *lead_to_cut);
void debug_get_tokens(Tokens *ptr);

static void verify_str_and_exit(char *ptr)
{
    if (ptr == NULL || ptr[0] == '\0')
    {
        fprintf(stderr, "[verify_str-err]: ptr must be a valid pointer!\n");
        exit(EXIT_FAILURE);
    }
}

static void verify_ptr_and_exit(void *ptr, const char *err_message)
{
    if (ptr == NULL)
    {
        fprintf(stderr, "%s\n", err_message);
        exit(EXIT_FAILURE);
    }
}

void init_tokens(Tokens *ptr)
{
    if (ptr->vector == NULL)
    {
        fprintf(stderr, "[init_tokens-err]: You cannot create a structure; it's already created.\n");
        return;
    }

    ptr = (Tokens *)malloc(sizeof(Tokens));
    if (ptr == NULL)
    {
        fprintf(stderr, "[init_tokens-err]: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    ptr->size = 0;
}

void free_vectors(Tokens *ptr)
{
    if (ptr == NULL)
        return;

    for (int i = 0; i < ptr->size; i++)
    {
        free(ptr->vector[i]);
    }
    free(ptr->vector);
    free(ptr);
}

void tokenize(Tokens *ptr, char phrase[], const char *lead_to_find)
{
    verify_ptr_and_exit((void *)ptr, "[tokenize-err]: invalid ptr structure");
    verify_str_and_exit((char *)phrase);
    verify_str_and_exit(lead_to_find);

    char *token = strtok(phrase, lead_to_find);

    while (token != NULL)
    {
        if (ptr->size == 0)
        {
            ptr->vector = (char **)malloc(sizeof(char **));
            if (ptr->vector == NULL)
            {
                fprintf(stderr, "[tokenizer-err]: Out of memory.");
                free_vectors(ptr);
                exit(EXIT_FAILURE);
            }
            ptr->vector[ptr->size] = (char *)malloc(sizeof(char **) * sizeof(token));
            if (ptr->vector[ptr->size] == NULL)
            {
                fprintf(stderr, "[tokenizer-err]: Out of memory.");
                free_vectors(ptr);
                exit(EXIT_FAILURE);
            }
            ptr->vector[sizeof(token)] = '\0';
        }
        else
        {
        }
    }
}
#endif
