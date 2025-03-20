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
static void verify_str_and_exit(const char *ptr);

void init_tokens(Tokens *ptr);
void free_vectors(Tokens *ptr);
void tokenize(Tokens *ptr, const char *prhase, const char *lead_to_cut);
void debug_get_tokens(Tokens *ptr);

static void verify_str_and_exit(const char *ptr)
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

void init_tokens(Tokens *ptr) // Stable
{
    ptr->vector = NULL;
    ptr->size = 0;
    puts("[init_tokens-debug]: Tokens init with success.");
}

void free_vectors(Tokens *ptr) // Stable
{
    if (ptr == NULL)

        return;

    for (int i = 0; i < ptr->size; i++)
    {

        printf("\n[free_vectors-debug]: Try to free pointer at %d position...\n", i);
        free(ptr->vector[i]);
    }

    free(ptr->vector);
}

void tokenize(Tokens *ptr, const char phrase[], const char *lead_to_find)
{
    verify_ptr_and_exit((void *)ptr, "[tokenize-err]: invalid ptr structure");
    verify_str_and_exit(phrase);
    verify_str_and_exit(lead_to_find);

    char *phraseMutable = strdup(phrase);
    char *token = strtok(phraseMutable, lead_to_find);
    if (token == NULL)
    {
        fprintf(stderr, "[tokenize-err]: buffer not capable to tokenize.");
        free_vectors(ptr);
        free(phraseMutable);
        exit(EXIT_FAILURE);
    }

    while (token != NULL)
    {
        phraseMutable = strtok(NULL, lead_to_find);

        if (ptr->size == 0)
        {
        }
        ptr->size++;
    }
    free(phraseMutable);
}

void debug_get_tokens(Tokens *ptr)
{
    verify_ptr_and_exit(ptr, "[debug_get_tokens-err]: invalid Tokens *ptr at function parameter.");
    for (int i = 0; i == ptr->size; i++)
    {
        printf("\nToken [%d]:%s", i, ptr->vector[i]);
    }
}
#endif
